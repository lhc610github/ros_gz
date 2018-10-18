/*
 * Copyright (C) 2018 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/

#include <atomic>
#include <chrono>
#include <csignal>
#include <iostream>
#include <string>
#include <thread>
#include <ignition/common/Image.hh>
#include <ignition/msgs.hh>
#include <ignition/transport.hh>
#include "../test_config.h"

/// \brief Flag used to break the publisher loop and terminate the program.
static std::atomic<bool> g_terminatePub(false);

//////////////////////////////////////////////////
/// \brief Function callback executed when a SIGINT or SIGTERM signals are
/// captured. This is used to break the infinite loop that publishes messages
/// and exit the program smoothly.
void signal_handler(int _signal)
{
  if (_signal == SIGINT || _signal == SIGTERM)
    g_terminatePub = true;
}

//////////////////////////////////////////////////
int main(int /*argc*/, char **/*argv*/)
{
  // Install a signal handler for SIGINT and SIGTERM.
  std::signal(SIGINT,  signal_handler);
  std::signal(SIGTERM, signal_handler);

  // Create a transport node and advertise a topic.
  ignition::transport::Node node;

  // ignition::msgs::Header.
  auto header_pub = node.Advertise<ignition::msgs::Header>("header");
  ignition::msgs::Header header_msg;
  ros1_ign_bridge::testing::createTestMsg(header_msg);

  // ignition::msgs::StringMsg.
  auto string_pub = node.Advertise<ignition::msgs::StringMsg>("string");
  ignition::msgs::StringMsg string_msg;
  ros1_ign_bridge::testing::createTestMsg(string_msg);

  // ignition::msgs::Quaternion.
  auto quaternion_pub =
    node.Advertise<ignition::msgs::Quaternion>("quaternion");
  ignition::msgs::Quaternion quaternion_msg;
  ros1_ign_bridge::testing::createTestMsg(quaternion_msg);

  // ignition::msgs::Vector3d.
  auto vector3_pub = node.Advertise<ignition::msgs::Vector3d>("vector3");
  ignition::msgs::Vector3d vector3_msg;
  ros1_ign_bridge::testing::createTestMsg(vector3_msg);

  // ignition::msgs::Image.
  auto image_pub = node.Advertise<ignition::msgs::Image>("image");
  ignition::msgs::Image image_msg;
  ros1_ign_bridge::testing::createTestMsg(image_msg);

  // ignition::msgs::IMU.
  auto imu_pub = node.Advertise<ignition::msgs::IMU>("imu");
  ignition::msgs::IMU imu_msg;
  ros1_ign_bridge::testing::createTestMsg(imu_msg);

  // ignition::msgs::LaserScan.
  auto laserscan_pub = node.Advertise<ignition::msgs::LaserScan>("laserscan");
  ignition::msgs::LaserScan laserscan_msg;
  ros1_ign_bridge::testing::createTestMsg(laserscan_msg);

  // ignition::msgs::Magnetometer.
  auto magnetic_pub = node.Advertise<ignition::msgs::Magnetometer>("magnetic");
  ignition::msgs::Magnetometer magnetometer_msg;
  ros1_ign_bridge::testing::createTestMsg(magnetometer_msg);

  // Publish messages at 1Hz.
  while (!g_terminatePub)
  {
    header_pub.Publish(header_msg);
    string_pub.Publish(string_msg);
    quaternion_pub.Publish(quaternion_msg);
    vector3_pub.Publish(vector3_msg);
    image_pub.Publish(image_msg);
    imu_pub.Publish(imu_msg);
    laserscan_pub.Publish(laserscan_msg);
    magnetic_pub.Publish(magnetometer_msg);

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

  return 0;
}
