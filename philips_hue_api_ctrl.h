/** ---------------------------------------------------------------------------
 * @file    philips_hue_api_ctrl.h
 * @brief   Philips hue API controller
 * @author  toms74209200 <https://github.com/toms74209200>
 * @date    2020/11/30
 * @copyright (c) 2020 toms74209200
 * This software is released under the MIT License.
 * http://opensource.org/licenses/mit-license.php
 *///--------------------------------------------------------------------------
#ifndef PHILIPS_HUE_API_CTRL_H_
#define PHILIPS_HUE_API_CTRL_H_

#include <WiFi.h>
#include <HTTPClient.h>

namespace philips_hue_api {

class controller {
    private:
    const String domain;
    String username;

    HTTPClient http_client;

    public:
    controller(const String &domain);
    String post_auth_user(String domain);
    String get_status_of_light(String light_id);
    String change_status_of_light(String light_id, bool on);
    void set_username(String username);
};

} // namespace philips_hue_api
#endif