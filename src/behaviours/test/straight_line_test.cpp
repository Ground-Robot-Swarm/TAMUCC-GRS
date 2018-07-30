#include <gtest/gtest.h>

#include "test_util.h"

#include "StraightLineBehavior.hpp"
#include "SwarmieInterface.hpp"

class StraightLineBehaviorTest : public testing::Test
{
protected:
   StraightLineBehavior sl;
   StraightLineBehaviorTest() : sl() {
      sl.SetLowerLevelAction(SwarmieAction(core::VelocityAction()));
      sl.Update();
   }
};

TEST_F(StraightLineBehaviorTest, movesForward)
{
   EXPECT_TRUE(is_moving(sl.GetAction()));
   EXPECT_FALSE(is_turning_left(sl.GetAction()));
   EXPECT_FALSE(is_turning_right(sl.GetAction()));
}

TEST_F(StraightLineBehaviorTest, isTurningKeepsTurning)
{
   SwarmieAction turn;
   turn.SetAction(core::VelocityAction(AngularVelocity(0,0,0.5)));
   sl.SetLowerLevelAction(turn);
   sl.Update();
   EXPECT_EQ(turn.GetVelocity().GetAngularMagnitude(), sl.GetAction().GetVelocity().GetAngularMagnitude());
   EXPECT_EQ(turn.GetVelocity().GetYaw(), sl.GetAction().GetVelocity().GetYaw());
   EXPECT_EQ(0, turn.GetVelocity().GetLinearMagnitude());
   EXPECT_FALSE(is_moving_forward(sl.GetAction()));
}

TEST_F(StraightLineBehaviorTest, isRotatingKeepsRotating)
{
   SwarmieAction turn;
   turn.SetAction(core::VelocityAction(AngularVelocity(0, 0, -0.6)));
   sl.SetLowerLevelAction(turn);
   sl.Update();
   EXPECT_EQ(turn.GetVelocity().GetYaw(), sl.GetAction().GetVelocity().GetYaw());
}
