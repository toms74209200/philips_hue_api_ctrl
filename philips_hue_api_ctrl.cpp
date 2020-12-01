/** ---------------------------------------------------------------------------
 * @file    philips_hue_api_ctrl.cpp
 * @brief   Philips hue API controller
 * @author  toms74209200 <https://github.com/toms74209200>
 * @date    2020/11/30
 * @copyright (c) 2020 toms74209200
 * This software is released under the MIT License.
 * http://opensource.org/licenses/mit-license.php
 *///--------------------------------------------------------------------------

#include "philips_hue_api_ctrl.h"

namespace philips_hue_api {

controller::controller(const String &domain)
    : domain(domain)
    {}

/** ---------------------------------------------------------------------------
 * @brief   Posts devicetype name and does user authentication
 * @param   devicetype  devicetype name
 * @return  response body. if HTTP status code is not 200, returns HTTP status code
 *///--------------------------------------------------------------------------
String controller::post_auth_user(String devicetype) {
    http_client.begin("http://"+domain+"/api");
    String request_body = "{\"devicetype\":\""+devicetype+"\"}";
    int http_code = http_client.POST(request_body);
    if (http_code != HTTP_CODE_OK) {
        return String(http_code);
    }
    return http_client.getString();
}

/** ---------------------------------------------------------------------------
 * @brief   Gets status of light.
 * @param   light_id    target light id
 * @return  response body. if HTTP status code is not 200, returns HTTP status code.
 * if username is not set, returns "Error".
 *///--------------------------------------------------------------------------
String controller::get_status_of_light(String light_id) {
    if (username.length() == 0) {
        return "Error";
    }
    http_client.begin("http://"+domain+"/api/"+username+"/lights/"+light_id);
    int http_code = http_client.GET();
    if (http_code != HTTP_CODE_OK) {
        return String(http_code);
    }
    return http_client.getString();
}

/** ---------------------------------------------------------------------------
 * @brief   Change status of light.
 * @param   light_id    target light id
 * @param   on          status to change
 * @return  response body. if HTTP status code is not 200, returns HTTP status code
 * if username is not set, returns "Error".
 *///--------------------------------------------------------------------------
String controller::change_status_of_light(String light_id, bool on) {
    if (username.length() == 0) {
        return "Error";
    }
    http_client.begin("http://"+domain+"/api/"+username+"/lights/"+light_id+"/state");
    String request_body = "";
    if (on) {
        request_body = "{\"on\":true, \"bri\":254}";
    } else {
        request_body = "{\"on\":false}";
    }
    int http_code = http_client.PUT(request_body);
    if (http_code != HTTP_CODE_OK) {
        return String(http_code);
    }
    return http_client.getString();
}

void controller::set_username(String username) {
    this->username = username;
}

} // namespace philips_hue_api