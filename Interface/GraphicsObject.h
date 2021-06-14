#pragma once

#include <string>

struct GraphicsObject
{
    constexpr void        SetErrorMessage(const std::string& errMsg) { m_errorMessage = errMsg; }
    constexpr std::string GetErrorMessage() const { return m_errorMessage; }

  private:
    std::string m_errorMessage;
};