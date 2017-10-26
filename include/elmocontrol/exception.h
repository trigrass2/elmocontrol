//

#ifndef ELMOCONTROL_EXCEPTION_H
#define ELMOCONTROL_EXCEPTION_H

#include <stdexcept>
#include <string>

namespace elmocontrol
{
class DeviceError : public std::runtime_error
{
 public:
  explicit DeviceError(const std::string &cause):
      std::runtime_error(cause) {}
};

}  // end namespace elmocontrol

#endif  // elmocontrol
