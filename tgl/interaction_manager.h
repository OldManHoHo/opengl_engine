#include <vector>

#include "tgl/actor.h"

namespace tgl
{
    
class InteractionManager
{
 public:
    virtual void tick(double time_delta, std::vector<tgl::Actor*>& actors);
};
    
}  // namespace tgl