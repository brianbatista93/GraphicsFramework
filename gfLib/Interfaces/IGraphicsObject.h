#pragma once

struct IGraphicsObject
{
    /**
     * @brief Sets an error message related to this graphics object.
     * @param errMsg Error message.
    */
    void SetErrorMessage(std::string&& errMsg) { m_errorMessage = std::move(errMsg); }
    void SetErrorMessage(const std::string& errMsg) { m_errorMessage = errMsg; }

    /**
     * @brief Returns the error message, if any, related to this graphics object.
     * @return The error message.
    */
    std::string GetErrorMessage() const { return m_errorMessage; }

  private:
    std::string m_errorMessage;
};