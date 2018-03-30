#include "c++/ModIOInstance.h"

namespace modio
{
  SetDownloadListenerCall* set_download_listener_call = NULL;    

  void onDownloadListener(u32 response_code, u32 mod_id)
  {
    if(set_download_listener_call)
      set_download_listener_call->callback(response_code, mod_id);
  }
}
