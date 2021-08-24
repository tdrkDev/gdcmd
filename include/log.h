#ifndef __GDCMD_LOG_H__
#define __GDCMD_LOG_H__

#define LOGE(fmt, args...)                                                     \
  printf("gdcmd: [%s():%d] E: " fmt, __func__, __LINE__, ##args);

#define LOGI(fmt, args...)                                                     \
  printf("gdcmd: [%s():%d] I: " fmt, __func__, __LINE__, ##args);

#define LOGW(fmt, args...)                                                     \
  printf("gdcmd: [%s():%d] W: " fmt, __func__, __LINE__, ##args);

#endif