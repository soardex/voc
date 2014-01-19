#ifndef _EMPEROR_SYSTEM_H_
#define _EMPEROR_SYSTEM_H_

#include <memory>

class CEmperorSystem
{
public:
    explicit CEmperorSystem();
    ~CEmperorSystem();

    void run();

private:
    class CImpl;
    std::unique_ptr<CImpl> m_pImpl;
};

#endif /* end of include guard: _EMPEROR_SYSTEM_H_ */
