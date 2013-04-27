#ifndef CONFIG_H_INCLUDED
#define CONFIG_H_INCLUDED

/* Sections */
#define GROUP_PREFS             "Preferences"
#define GROUP_LOGIN             "Login"

/* Options */
#define X_DISPLAY_CFG           "x_display"
#define SEND_DELAY_CFG          "send_delay"
#define SAVE_LOGIN_CFG          "save_login_data"
#define SAVE_PASS_CFG           "save_pass"
#define AUTO_CONNECT_CFG        "auto_connect"
#define USERNAME_CFG            "username"
#define HOSTNAME_CFG            "hostname"
#define PASSWORD_CFG            "password"

#define DEFAULT_X_DISPLAY       ":0.0"
#define DEFAULT_SEND_DELAY      100000

/* Handlers */
int load_config( const char* filename );
int save_config( const char* filename );

#endif // CONFIG_H_INCLUDED

