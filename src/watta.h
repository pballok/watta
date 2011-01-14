#ifndef WATTA_H
#define WATTA_H

#include <logger.h>
#include <tracer.h>
#include <qtmysqlconnection.h>
#include <sevexception.h>

#include "preferences.h"

extern cLogger             g_obLogger;
extern cQTMySQLConnection *g_poDB;
extern cPreferences       *g_poPrefs;

#endif // WATTA_H
