#pragma once 
#include "Executor.hpp"
namespace adas
{
class ExecutorImpl final : public Executor
{
public:
    explicit ExecutorImpl(const Pose& pose) noexcept;
    ~ExecutorImpl() noexcept = default;
    
    ExecutorImpl(const ExecutorImpl&) = delete;
    ExecutorImpl& operator=(const ExecutorImpl&) = delete;

public:
    void Execute(const std::string& command) noexcept override;
    Pose Query(void) const noexcept override;


private:
    class ICommand {// p24
    public:
        virtual ~ICommand() = default;
        virtual void DoOperate(ExecutorImpl& executor) const noexcept = 0;
    };

    class MoveCommand final :public ICommand {// ← 嵌套在 ExecutorImpl 里面
    public:
        void DoOperate(ExecutorImpl& executor) const noexcept override
        {
            if (executor.IsFast()) {
                executor.Move();  // 快进：多走一格
            }
            executor.Move();  // 真正的活还是 Move() 干的
        }
    };

    class TurnLeftCommand final : public ICommand
    {  // ← 嵌套在 ExecutorImpl 里面
    public:
        void DoOperate(ExecutorImpl& executor) const noexcept override
        {
            if (executor.IsFast()) {
                executor.Move();  // 快进：多走一格
            }
            executor.TurnLeft();  
        }
    };

    class TurnRightCommand final : public ICommand
    {  // ← 嵌套在 ExecutorImpl 里面
    public:
        void DoOperate(ExecutorImpl& executor) const noexcept override
        {
            if (executor.IsFast()) {
                executor.Move();  // 快进：多走一格
            }
            executor.TurnRight();
        }
    };

    class FastCommand final : public ICommand
    {
    public:
        void DoOperate(ExecutorImpl& executor) const noexcept override
        {
            executor.Fast();
        }
    };

    Pose pose;
    void Move(void) noexcept;
    void TurnLeft(void) noexcept;
    void TurnRight(void) noexcept;

    void Fast(void) noexcept;
    bool IsFast(void) const noexcept;
    bool fast{false};
};
}// namespace adas
