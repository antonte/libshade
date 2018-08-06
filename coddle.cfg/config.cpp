#include "coddle/config.hpp"

void configure(Config &cfg)
{
  cfg.common.cflags.push_back("-D_GLIBCXX_DEBUG");
  cfg.getLib(cfg, "sdlpp", "master");
}
