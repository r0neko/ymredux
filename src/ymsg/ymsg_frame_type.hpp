// MIT License
//
// Copyright (c) 2024 r0neko
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef YMSG_FRAME_TYPE_GUARD
#define YMSG_FRAME_TYPE_GUARD

#include <cstdint>

namespace ymsg {
    enum YES_ : uint16_t {
        YES_USER_LOGIN = 1,
        YES_USER_LOGOFF = 2,
        YES_USER_AWAY = 3,
        YES_USER_BACK = 4,
        YES_USER_GET_MSGS = 5,
        YES_USER_HAS_MSG = 6,
        YES_ACTIVATE_ID = 7,
        YES_DEACTIVATE_ID = 8,
        YES_GET_USER_STATUS = 10,
        YES_USER_HAS_MAIL = 11,
        YES_START_CONFERENCE = 12,
        YES_CALENDAR_ALERT = 13,
        YES_USER_PERSONAL_MESSAGE = 14,
        YES_UPDATE_BUDDY_LIST = 15,
        YES_UPDATE_ID_LIST = 16,
        YES_UPDATE_IGNORE_LIST = 17,
        YES_PING = 18,
        YES_UPDATE_GROUP = 19,
        YES_SYSTEM_MESSAGE = 20,
        YES_CLIENT_STATS = 21,
        YES_CLIENT_ALERT_STATS = 22,
        YES_GROUP_MESSAGE = 23,
        YES_HOST_CONFERENCE = 24,
        YES_JOIN_CONFERENCE = 25,
        YES_DECLINE_CONFERENCE = 26,
        YES_LEAVE_CONFERENCE = 27,
        YES_INVITE_CONFERENCE = 28,
        YES_SAY_CONFERENCE = 29,
        YES_CHAT_LOGIN = 30,
        YES_CHAT_LOGOFF = 31,
        YES_CHAT_MSG = 32,
        YES_GAMES_USER_LOGIN = 40,
        YES_GAMES_USER_LOGOFF = 41,
        YES_GAMES_USER_HAS_MSG = 42,
        YES_NET2PHONE_STATS = 44,
        YES_ADDRESSBOOK_ALERT = 51,
        YES_AUCTION_ALERT = 60,
        YES_USER_FT = 70,
        YES_USER_FT_REPLY = 71,
        YES_USER_CONVERSE = 72,
        YES_USER_WEBTOUR = 73,
        YES_IM_ENABLE_VOICE = 74,
        YES_USER_SEND_MESG = 75,
        YES_SEND_PORT_CHECK = 76,
        YES_SEND_DATA_THRU = 77,
        YES_P2P_START = 79,
        YES_MSGR_WEBCAM_TOKEN = 80,
        YES_STATS = 81,
        YES_USER_LOGIN_2 = 84,
        YES_PRELOGIN_DATA = 85,
        YES_GET_COOKIE_DATA = 86,
        YES_HELO = 87,
        YES_FEATURE_NOT_SUPPORTED = 88,
        YES_ADD_BUDDY = 131,
        YES_REMOVE_BUDDY = 132,
        YES_MODIFY_IGNORE_LIST = 133,
        YES_DENY_BUDDY_ADD = 134,
        YES_RENAME_GROUP = 137,
        YES_KEEP_ALIVE = 138,
        YES_YPC_ADD_FRIEND_APPROVAL = 139,
        YES_CHALLENGE = 140,
        YES_ADD_BUDDY_INSTANT_APPROVAL = 141,
        YES_CHAT_MSGR_USER_LOGIN = 150,
        YES_CHAT_GOTO_USER = 151,
        YES_CHAT_ROOM_JOIN = 152,
        YES_CHAT_ROOM_PART = 155,
        YES_CHAT_ROOM_INVITE = 157,
        YES_CHAT_MSGR_USER_LOGOFF = 160,
        YES_CHAT_PING = 161,
        YES_CHAT_WEBCAM_TOKEN = 167,
        YES_CHAT_PUBLIC_MSG = 168,
        YES_CHAT_ROOM_CREATE = 169,
        YES_GAMES_INVITE = 183,
        YES_GAMES_SEND_DATA = 184,
        YES_EDIT_INVISIBLE_TO_LIST = 185,
        YES_EDIT_VISIBLE_TO_LIST = 186,
        YES_ANTIBOT = 187,
        YES_AVATAR_CHANGED = 188,
        YES_FRIEND_ICON = 189,
        YES_FRIEND_ICON_DOWNLOAD = 190,
        YES_AVATAR_GET_FILE = 191,
        YES_AVATAR_GET_HASH = 192,
        YES_DISPLAY_TYPE_CHANGED = 193,
        YES_FRIEND_ICON_FT = 194,
        YES_GET_COOKIE = 195,
        YES_ADDRESS_BOOK_CHANGED = 196,
        YES_SET_VISIBILITY = 197,
        YES_SET_AWAY_STATUS = 198,
        YES_DISPLAY_IMAGE_PREFS = 199,
        YES_VERIFY_USER = 200,
        YES_AUDIBLE = 208,
        YES_IM_PANEL_FEATURE = 210,
        YES_SHARE_CONTACTS = 211,
        YES_IM_SESSION = 212,
        YES_SUBSCRIPTION = 213,
        YES_BUDDY_AUTHORIZE = 214,
        YES_PHOTO_ADD = 215,
        YES_PHOTO_SELECT = 216,
        YES_PHOTO_DELETE = 217,
        YES_PHOTO_FILE_REQUEST = 218,
        YES_PHOTO_POINTER = 219,
        YES_FXFER_INVITE = 220,
        YES_FXFER_SEND = 221,
        YES_FXFER_RECEIVE = 222,
        YES_UPDATE_CAPABILITY = 223,
        YES_REPORT_SPIM = 224,
        YES_MINGLE_DATA = 225,
        YES_ALERT = 226,
        YES_APP_REGISTRY = 227,
        YES_NEW_USER = 228,
        YES_ACCEPT_MSGR_INVITE = 229,
        YES_MSGR_USAGE = 230,
        YES_BUDDY_MOVE = 231,
        YES_GET_VOICE_CRUMB = 232,
        YES_PLUGIN_SESSION_INITIATION = 233,
        YES_APPLICATION_MESSAGE = 234,
        YES_APPLICATION_PRESENCE = 235,
        YES_FXFER_PLUGIN_INVITE = 236,
        YES_PC2MOBILE_FXFER = 237,
        YES_PREFERENCE = 239,
        YES_BUDDY_INFO = 240,
        YES_BUDDY_LIST = 241,
        YES_CHECK_PREMIUM_SMS_BALANCE = 242,
        YES_WIDGET_BUDDY_LIST = 252,
        YES_WIDGET_BUDDY_INFO = 253,
        YES_WIDGET_ACTION = 254,
        YES_NEWS_ALERTS = 300,
        YES_CORP_USER_LOGIN = 450,
        YES_MSGREE_LOGIN = 451,
        YES_CORP_ID_COPRP2PINIT = 452,
        YES_CORP_CHAT_MSG = 453,
        YES_CORP_GAMES_USER_HAS_MSG = 454,
        YES_SECURE_USER_LOGIN = 460,
        YES_SECURE_IM_MSG = 461,
        YES_SECURE_CHAT_SAY_MESG = 463,
        YES_SECURE_GAMES_USER_HAS_MSG = 464,
        YES_SYMANTEC_MSGS = 500,
        YES_MOBILE_SEND_SMS_MESSAGE = 746,
        YES_MOBILE_SMS_LOGIN = 748,
        YES_MOBILE_SMS_NUMBER = 749,
        YES_ANON_LOGOFF = 802,
        YES_ANON_HAS_MSG = 806,
        YES_CLIENT_NETSTAT = 1000,
        YES_P2P_USER = 1001,
        YES_P2P_STATE = 1002,
        YES_LWM_LOGIN = 1100,
        YES_LWM_LOGOFF = 1101,
        YES_OPI_LOGIN = 1102,
        YES_OPI_LOGOFF = 1103,
        YES_OPI_IM = 1104,
        YES_USER_HAS_OPI_MESSAGE = 1105,
        YES_LWMOPI_CHECKLOGIN = 1106,
        YES_LWMOPI_STARTOPI = 1107,
        YES_LWMOPI_STOPOPI = 1108
    };
}

#endif //YMSG_FRAME_TYPE_GUARD
