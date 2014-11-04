#ifndef _PACKET_GG_HPP_
#define _PACKET_GG_HPP_

#ifdef HAVE_CONFIG_H
# include "config.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#include <epan/packet.h>

#ifdef __cplusplus
}
#endif

#define DEFAULT_GG_PORT 8074

extern dissector_handle_t json_dissector;

#endif /* _PACKET_GG_HPP_ */
