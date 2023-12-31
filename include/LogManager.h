#ifndef __LOG_MANAGER_H__
#define __LOG_MANAGER_H__

#include "Manager.h"

#define LM df::LogManager::getInstance()

namespace df {

extern const char *LOGFILE_NAME;

class LogManager : public Manager {
 private:
  LogManager();
  LogManager(LogManager const &);
  void operator=(LogManager const &);
  bool m_do_flush;
  FILE *m_p_f;

 public:
  ~LogManager();
  static LogManager &getInstance();
  int startUp() override;
  void shutDown() override;
  void setFlush(bool do_flush = true);
  int writeLog(const char *fmt, ...) const;
  // To be used when the logger is not yet initialized
  void stdoutLog(const char *fmt, ...) const;
};

}  // namespace df

#endif