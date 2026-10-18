#include <gtest/gtest.h>

#include <memory>
#include <tuple>

#include "Executor.hpp"

namespace adas
{
bool operator==(const Pose& lhs, const Pose& rhs)
{
    // 为 Pose 定义 == 运算符重载，使测试中比较 Pose 对象简单明了，std::tie 提高可读性
    return std::tie(lhs.x, lhs.y, lhs.heading) == std::tie(rhs.x, rhs.y, rhs.heading);
}

// 测试套名 ExecutorTest；用例名描述"给定条件 + 预期行为"
TEST(ExecutorTest, should_return_init_pose_when_without_command)
{
    // given
    std::unique_ptr<Executor> executor(Executor::NewExecutor({0, 0, 'E'}));

    // when

    // then
    const Pose target({0, 0, 'E'});
    ASSERT_EQ(target, executor->Query());
}
}  // namespace adas
