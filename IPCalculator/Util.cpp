#include "Util.h"

int Util::identifyAddress(const InternetAddress& addr) {
    if (addr.isNetworkAddress())
        return 0;
    else if (addr.isBroadcastAddress())
        return 1;
    else
        return 2;
}