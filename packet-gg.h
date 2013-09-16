#ifndef _PACKET_GG_H
#define _PACKET_GG_H

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#include <epan/packet.h>

#define DEFAULT_GG_PORT	8074

extern const char version[];
extern void plugin_register(void);
extern void plugin_reg_handoff(void);
extern gint ett_gg;

#endif
