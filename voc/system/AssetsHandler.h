#ifndef _ASSETS_HANDLER_H_
#define _ASSETS_HANDLER_H_

#include <FreeImage.h>
#include <map>
#include "../Commons.h"

class CTextureManager
{
public:
    static CTextureManager *inst()
    {
        if (!m_psInst)
            m_psInst = new CTextureManager();

        return m_psInst;
    }

    ~CTextureManager()
    {
        unloadAllTextures();
        m_psInst = 0;
    }

    bool load(const char *filename, const unsigned int textureId,
            GLenum imageFormat = GL_RGB,
            GLint internalFormat = GL_RGB,
            GLint level = 0,
            GLint border = 0)
    {
        FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
        FIBITMAP *dib = 0;
        BYTE *bits = 0;

        unsigned int width = 0, height = 0;
        unsigned int glTextureId;

        fif = FreeImage_GetFileType(filename, 0);
        if (fif == FIF_UNKNOWN)
            fif = FreeImage_GetFIFFromFilename(filename);

        if (fif == FIF_UNKNOWN)
            return false;

        if (FreeImage_FIFSupportsReading(fif))
            dib = FreeImage_Load(fif, filename);

        if (!dib)
            return false;

        bits = FreeImage_GetBits(dib);
        width = FreeImage_GetWidth(dib);
        height = FreeImage_GetHeight(dib);

        if ((bits == 0) || (width == 0) || (height == 0))
            return false;

        if (m_mTextureId.find(textureId) != m_mTextureId.end())
            glDeleteTextures(1, &(m_mTextureId[textureId]));

        glGenTextures(1, &glTextureId);
        m_mTextureId[textureId] = glTextureId;
        glBindTexture(GL_TEXTURE_2D, glTextureId);
        glTexImage2D(GL_TEXTURE_2D, level, internalFormat,
                width, height, border, imageFormat,
                GL_UNSIGNED_BYTE, bits);

        FreeImage_Unload(dib);
        return true;
    }

    bool unloadTexture(const unsigned int textureId)
    {
        bool result = true;

        if (m_mTextureId.find(textureId) != m_mTextureId.end())
        {
            glDeleteTextures(1, &(m_mTextureId[textureId]));
            m_mTextureId.erase(textureId);
        }
        else
            result = false;

        return result;
    }

    bool bindTexture(const unsigned int textureId)
    {
        bool result = true;

        if (m_mTextureId.find(textureId) != m_mTextureId.end())
            glBindTexture(GL_TEXTURE_2D, m_mTextureId[textureId]);
        else
            result = false;

        return result;
    }

    void unloadAllTextures()
    {
        std::map<unsigned int, unsigned int>::iterator i = m_mTextureId.begin();
        while (i != m_mTextureId.end())
            unloadTexture(i->first);

        m_mTextureId.clear();
    }

protected:
    CTextureManager();
    CTextureManager(const CTextureManager& tm);
    CTextureManager& operator=(const CTextureManager& tm);

    static CTextureManager *m_psInst;
    std::map<unsigned int, unsigned int> m_mTextureId;
};

CTextureManager *CTextureManager::m_psInst = 0;

#include <assimp/assimp.h>
#include <assimp/aiScene.h>
#include <assimp/aiPostProcess.h>

class ModelLoader
{
public:
    void init()
    {
        aiLogStream stream;

        stream = aiGetPredefinedLogStream(aiDefaultLogStream_STDOUT, NULL);
        aiAttachLogStream(&stream);
    }

    void destroy()
    {
        aiReleaseImport(m_psScene);
        aiDetachAllLogStreams();
    }

    int load(const char *filename)
    {
        aiImportFile(filename, aiProcessPreset_TargetRealtime_MaxQuality);
        m_psScene = aiImportFile(filename, aiProcessPreset_TargetRealtime_MaxQuality);

        if (m_psScene)
        {
            getBoundingBox(&m_sSceneMin, &m_sSceneMax);
            m_sSceneCenter.x = (m_sSceneMin.x + m_sSceneMax.x) / 2.0f;
            m_sSceneCenter.y = (m_sSceneMin.y + m_sSceneMax.y) / 2.0f;
            m_sSceneCenter.z = (m_sSceneMin.z + m_sSceneMax.z) / 2.0f;
            return 0;
        }
        return 1;
    }

    void render()
    {
        float tmp;

        //! rotate it around the y axis
        //glRotatef(90.0f, 0.f, 1.f, 0.f);

        //! scale the whole asset to fit into the view frustum
        tmp = m_sSceneMax.x - m_sSceneMin.x;
        tmp = std::max(m_sSceneMax.y - m_sSceneMin.y, tmp);
        tmp = std::max(m_sSceneMax.z - m_sSceneMin.z, tmp);
        tmp = 1.0f / tmp;
        glScalef(tmp, tmp, tmp);

        //! center the asset
        glTranslatef(-m_sSceneCenter.x, -m_sSceneCenter.y, -m_sSceneCenter.z);

        if (m_nSceneList == 0)
        {
            m_nSceneList = glGenLists(1);
            glNewList(m_nSceneList, GL_COMPILE);
            recursiveRender(m_psScene, m_psScene->mRootNode);
            glEndList();
        }

        glCallList(m_nSceneList);
    }

    void recursiveRender(const aiScene *sc, const aiNode *nd)
    {
        unsigned int i;
        unsigned int n = 0, t;

        aiMatrix4x4 m = nd->mTransformation;

        aiTransposeMatrix4(&m);
        glPushMatrix();
        glMultMatrixf((float*)&m);

        for (; n < nd->mNumMeshes; ++n)
        {
            aiMesh *mesh = m_psScene->mMeshes[nd->mMeshes[n]];
            if (mesh->mNormals == NULL)
                glDisable(GL_LIGHTING);
            else
                glEnable(GL_LIGHTING);

            for (t = 0; t < mesh->mNumFaces; ++t)
            {
                const aiFace *face = &mesh->mFaces[t];
                GLenum faceMode;

                switch(face->mNumIndices)
                {
                    case 1: faceMode = GL_POINTS; break;
                    case 2: faceMode = GL_LINES; break;
                    case 3: faceMode = GL_TRIANGLES; break;
                    default: faceMode = GL_POLYGON; break;
                }

                glBegin(faceMode);
                    for (i = 0; i < face->mNumIndices; i++)
                    {
                        int index = face->mIndices[i];
                        if (mesh->mColors[0] != NULL)
                            glColor4fv((GLfloat*)&mesh->mColors[0][index]);

                        if (mesh->mNormals != NULL)
                            glNormal3fv(&mesh->mNormals[index].x);

                        glVertex3fv(&mesh->mVertices[index].x);
                    }
                glEnd();
            }
        }

        for (n = 0; n < nd->mNumChildren; ++n)
            recursiveRender(sc, nd->mChildren[n]);

        glPopMatrix();
    }

    void getBoundingBoxForNode(const aiNode *nd,
            aiVector3D *min,
            aiVector3D *max,
            aiMatrix4x4 *trafo)
    {
        aiMatrix4x4 prev;
        unsigned int n = 0, t;

        prev = *trafo;
        aiMultiplyMatrix4(trafo, &nd->mTransformation);
        
        for (; n < nd->mNumMeshes; ++n)
        {
            const aiMesh *mesh = m_psScene->mMeshes[nd->mMeshes[n]];
            for (t = 0; t < mesh->mNumVertices; ++t)
            {
                aiVector3D tmp = mesh->mVertices[t];
                aiTransformVecByMatrix4(&tmp, trafo);

                min->x = std::min(min->x, tmp.x);
                min->y = std::min(min->y, tmp.y);
                min->z = std::min(min->z, tmp.z);

                max->x = std::max(max->x, tmp.x);
                max->y = std::max(max->y, tmp.y);
                max->z = std::max(max->z, tmp.z);
            }
        }

        for (n = 0; n < nd->mNumChildren; ++n)
            getBoundingBoxForNode(nd->mChildren[n], min, max, trafo);

        *trafo = prev;
    }

    void getBoundingBox(aiVector3D *min, aiVector3D *max)
    {
        aiMatrix4x4 trafo;
        aiIdentityMatrix4(&trafo);

        min->x = min->y = min->z = 1e10f;
        max->x = max->y = max->z = -1e10f;

        getBoundingBoxForNode(m_psScene->mRootNode, min, max, &trafo);
    }

protected:
    const aiScene *m_psScene;
    aiVector3D m_sSceneMin;
    aiVector3D m_sSceneMax;
    aiVector3D m_sSceneCenter;

    unsigned int m_nSceneList;
};

#endif /* end of include guard: _ASSETS_HANDLER_H_*/
