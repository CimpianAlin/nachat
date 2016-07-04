#include "Member.hpp"

#include "proto.hpp"

namespace matrix {

void Member::dispatch(const proto::Event &state) {
  auto membership = state.content["membership"].toString();
  bool old_invite_pending = invite_pending_;
  if(membership == "invite") {
    invite_pending_ = true;
  } else if(membership == "join") {
    invite_pending_ = false;
  }
  if(invite_pending_ != old_invite_pending) {
    invite_pending_changed();
  }

  auto i = state.content.find("displayname");
  if(i != state.content.end()) {
    display_name_ = i->toString();
  }
  i = state.content.find("avatar_url");
  if(i != state.content.end()) {
    auto old_avatar = avatar_url_;
    auto str = i->toString();
    if(str == "") {
      avatar_url_ = QUrl();
    } else {
      avatar_url_ = QUrl(str);
    }
    avatar_url_changed();
  }
}

}