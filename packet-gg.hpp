#ifndef _PACKET_GG_HPP_
#define _PACKET_GG_HPP_

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

extern "C" {

#include <epan/packet.h>

}

#define DEFAULT_GG_PORT 8074

extern dissector_handle_t json_dissector;

#endif /* _PACKET_GG_HPP_ */
