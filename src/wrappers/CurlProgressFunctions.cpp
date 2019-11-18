#include "wrappers/CurlProgressFunctions.h"
#include "c++/schemas/QueuedModDownload.h"
#include "c++/schemas/QueuedModfileUpload.h"

namespace modio
{
namespace curlwrapper
{

i32 onModDownloadProgress(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow)
{
  QueuedModDownload *queued_mod_download = (QueuedModDownload *)clientp;
  queued_mod_download->current_progress = dlnow;
  queued_mod_download->total_size = dltotal;

  if(queued_mod_download->state == MODIO_MOD_PAUSING)
  {
    writeLogLine("Download paused at " + toString(dlnow), MODIO_DEBUGLEVEL_LOG);      
    updateModDownloadQueueFile();    
    return -1;
  }

  if(queued_mod_download->state == MODIO_PRIORITIZING_OTHER_DOWNLOAD)
  {
    writeLogLine("Download paused at " + toString(dlnow) + " in order to prioritize other download.", MODIO_DEBUGLEVEL_LOG);      
    return -1;
  }

  if(dltotal!=0)
    queued_mod_download->state = MODIO_MOD_DOWNLOADING;

  return 0;
}

i32 onModUploadProgress(void *clientp, double dltotal, double dlnow, double ultotal, double ulnow)
{
  QueuedModfileUpload *queued_mod_upload = (QueuedModfileUpload*)clientp;
  queued_mod_upload->current_progress = ulnow;
  queued_mod_upload->total_size = ultotal;

  if(ultotal!=0)
    queued_mod_upload->state = MODIO_MOD_UPLOADING;
  
  return 0;
}

}
}
