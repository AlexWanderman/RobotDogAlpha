#pragma once

#include <vector>
#include <Arduino.h>
#include <mcp2515_can.h>

#include "input_controller/command.hpp"

#include "commands.hpp"
#include "limits.hpp"

class MotorController
{
public:
  MotorController(mcp2515_can *can1, std::vector<Command> *commands);
  void loop();

private:
  mcp2515_can *_can1;
  std::vector<Command> *_commands;
  const int _delay = 10;

  void _start_motor(mcp2515_can *can, unsigned long id,                             // CAN bus and CAN ID
                    unsigned long *m_id, float *m_pos, float *m_vel, float *m_trq); // Motor parameters

  void _stop_motor(mcp2515_can *can, unsigned long id,                             // CAN bus and CAN ID
                   unsigned long *m_id, float *m_pos, float *m_vel, float *m_trq); // Motor parameters

  void _zero_motor(mcp2515_can *can, unsigned long id,                             // CAN bus and CAN ID
                   unsigned long *m_id, float *m_pos, float *m_vel, float *m_trq); // Motor parameters

  void _check_motor(mcp2515_can *can, unsigned long id,                             // CAN bus and CAN ID
                    unsigned long *m_id, float *m_pos, float *m_vel, float *m_trq); // Motor parameters

  void _control_motor(mcp2515_can *can, unsigned long id,                             // CAN bus and CAN ID
                      float new_position, float new_stiffness, float new_damper,      // New parameters
                      unsigned long *m_id, float *m_pos, float *m_vel, float *m_trq); // Motor parameters

  unsigned int _float_to_uint(float x, float x_min, float x_max, float bits);
  float _uint_to_float(unsigned int x_int, float x_min, float x_max, float bits);

  byte _can_pack(mcp2515_can *can, unsigned long id, float new_position, float new_stiffness, float new_damper); // Control
  byte _can_unpack(mcp2515_can *can, unsigned long id, unsigned long *m_id, float *m_pos, float *m_vel, float *m_trq);
};
