#include "c/methods/callbacks/ImageCallbacks.h"
#include "Utility.h" // for hasKey

std::map<u32, DownloadImageParams *> download_image_callbacks;

void modioOnImageDownloaded(u32 call_number, u32 response_code)
{
  ModioResponse response;
  nlohmann::json empty_json;
  modioInitResponse(&response, empty_json);
  response.code = response_code;

  fclose(download_image_callbacks[call_number]->file);
  
  download_image_callbacks[call_number]->callback(download_image_callbacks[call_number]->object, response);
  
  delete download_image_callbacks[call_number];
  download_image_callbacks.erase(call_number);
  
  modioFreeResponse(&response);
}

void clearImageCallbackParams()
{
  for (auto download_image_callback : download_image_callbacks)
    delete download_image_callback.second;
  download_image_callbacks.clear();
}
