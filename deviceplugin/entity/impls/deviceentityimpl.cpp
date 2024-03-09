#include "deviceentityimpl.h"
#include "deviceplugin/consts.h"

#include <iostream>

#include <QDebug>


DeviceEntityImpl::DeviceEntityImpl(const std::shared_ptr<DeviceEntityDTO> &dto): _dto(dto) {

}

std::string DeviceEntityImpl::getDeviceName() {
  std::string result = "";

  if (_dto != nullptr) {
    result = _dto->name;
  }

  return result;
}

void DeviceEntityImpl::setDeviceName(const std::string &name) {
  if (_dto != nullptr) {
    _dto->name = name;
  }
}

std::string DeviceEntityImpl::getDeviceDescription() {
  std::string result = "";

  if (_dto != nullptr) {
    result = _dto->description;
  }

  return result;
}

void DeviceEntityImpl::setDeviceDescription(const std::string &description) {
  if (_dto != nullptr) {
    _dto->description = description;
  }
}

DeviceState DeviceEntityImpl::getDeviceState() {
  return _current_state_key;
}


void DeviceEntityImpl::setConnectionStatus(bool connection_status) {
  if (connection_status) {
    changeState(CONNECTED);
    std::cout << "CHANGED:::::" << CONNECTED << std::endl;
  } else {
    changeState(NOT_CONNECTED);
  }
}

bool DeviceEntityImpl::getConnectionStatus() {
  auto result = false;

  if (_reg_card != nullptr) {
    result = _reg_card->getConnectionStatus();
    setConnectionStatus(result);
  }

  return result;
}

ErrorCode DeviceEntityImpl::connect() {
  auto result = OPERATION_INTERRUPTED;

  if (_reg_card != nullptr) {
    result = _reg_card->connect();
    getConnectionStatus();
  }

  return result;
}

ErrorCode DeviceEntityImpl::disconnect() {
  auto result = OPERATION_INTERRUPTED;

  if (_reg_card != nullptr) {
    result = _reg_card->disconnect();
    getConnectionStatus();
  }

  return result;
}

void DeviceEntityImpl::addState(const std::pair<DeviceState, std::shared_ptr<DeviceEntityState>> &state) {
  _states.insert(state);
}

void DeviceEntityImpl::setRegCard(const std::shared_ptr<DeviceEntityRegCard> &reg_card) {
  _reg_card = reg_card;
}

void DeviceEntityImpl::changeState(DeviceState state) {
  std::cout << "Connection change state " << state << " " << __func__ << std::endl;
  if (_states.count(state) != 0) {

    bool to_load_dto = false;
    if (_current_state_key != state && state == CONNECTED) {
      to_load_dto = true;
      std::cout << "TO LOAD DTO " << to_load_dto << " " << __func__ << std::endl;
    }

    _current_state_key = state;
    _current_state = _states[state];

    if (to_load_dto) {
      loadDeviceDTO(_dto);
    }


    std::cout << "CURRENT STATE CHANGED to " << state << " " << __func__ << std::endl;
  }
}

void DeviceEntityImpl::process() {
  if (_reg_card != nullptr) {
    _reg_card->updateRegCard();
  }
}

GetChannelDelayResponse DeviceEntityImpl::getChannelsDelay(GetChannelDelayRequest request) {
  GetChannelDelayResponse response{};

  if (_current_state != nullptr) {
    response = _current_state->getChannelsDelay(request);
  } else {
    qCritical() << "Current state is nullptr " << __func__;
  }

  return response;
}

int DeviceEntityImpl::getChannelCount() {
  int response = 0;

  if (_current_state != nullptr) {
    response = _current_state->getChannelCount();
  } else {
    qCritical() << "Current state is nullptr " << __func__;
  }

  return response;
}
GetSyncModuleStatusesResponse DeviceEntityImpl::getSyncModuleStatuses(GetSyncModuleStatusesRequest request) {
  GetSyncModuleStatusesResponse response{};

  if (_current_state != nullptr) {
    response = _current_state->getSyncModuleStatuses(request);
  } else {
    qCritical() << "Current state is nullptr " << __func__;
  }

  return response;
}
GetSFPParametersResponse DeviceEntityImpl::getSFPParameters(GetSFPParametersRequest request) {
  GetSFPParametersResponse response{};

  if (_current_state != nullptr) {
    response = _current_state->getSFPParameters(request);
  } else {
    qCritical() << "Current state is nullptr " << __func__;
  }

  return response;
}
GetChannelWidthResponse DeviceEntityImpl::getChannelsWidth(GetChannelWidthRequest request) {
  GetChannelWidthResponse response{};

  if (_current_state != nullptr) {
    response = _current_state->getChannelsWidth(request);
  } else {
    qCritical() << "Current state is nullptr " << __func__;
  }

  return response;
}

GetChannelEnabledStatusResponse DeviceEntityImpl::getChannelsEnabledStatus(GetChannelEnabledStatusRequest request) {
  GetChannelEnabledStatusResponse response{};

  if (_current_state != nullptr) {
    response = _current_state->getChannelsEnabledStatus(request);
  } else {
    qCritical() << "Current state is nullptr " << __func__;
  }

  return response;
}

GetChannelInvertedStatusResponse DeviceEntityImpl::getChannelsInvertedStatus(GetChannelInvertedStatusRequest request) {
  GetChannelInvertedStatusResponse response{};

  if (_current_state != nullptr) {
    response = _current_state->getChannelsInvertedStatus(request);
  } else {
    qCritical() << "Current state is nullptr " << __func__;
  }

  return response;
}

GetChannelStartModeResponse DeviceEntityImpl::getChannelsStartMode(GetChannelStartModeRequest request) {
  GetChannelStartModeResponse response{};

  if (_current_state != nullptr) {
    response = _current_state->getChannelsStartMode(request);
  } else {
    qCritical() << "Current state is nullptr " << __func__;
  }

  return response;
}

GetChannelStartSourceResponse DeviceEntityImpl::getChannelsStartSource(GetChannelStartSourceRequest request) {
  GetChannelStartSourceResponse response{};

  if (_current_state != nullptr) {
    response = _current_state->getChannelsStartSource(request);
  } else {
    qCritical() << "Current state is nullptr " << __func__;
  }

  return response;
}
SetChannelDelayResponse DeviceEntityImpl::setChannelDelay(SetChannelDelayRequest request) {
  SetChannelDelayResponse response{};

  if (_current_state != nullptr) {
    response = _current_state->setChannelDelay(request);
  } else {
    qCritical() << "Current state is nullptr " << __func__;
  }

  return response;
}
SetChannelWidthResponse DeviceEntityImpl::setChannelWidth(SetChannelWidthRequest request) {
  SetChannelWidthResponse response{};

  if (_current_state != nullptr) {
    response = _current_state->setChannelWidth(request);
  } else {
    qCritical() << "Current state is nullptr " << __func__;
  }

  return response;
}
SetChannelEnabledStatusResponse DeviceEntityImpl::setChannelEnabledStatus(SetChannelEnabledStatusRequest request) {
  SetChannelEnabledStatusResponse response{};

  if (_current_state != nullptr) {
    response = _current_state->setChannelEnabledStatus(request);
  } else {
    qCritical() << "Current state is nullptr " << __func__;
  }

  return response;
}
SetChannelInvertedStatusResponse DeviceEntityImpl::setChannelInvertedStatus(SetChannelInvertedStatusRequest request) {
  SetChannelInvertedStatusResponse response{};

  if (_current_state != nullptr) {
    response = _current_state->setChannelInvertedStatus(request);
  } else {
    qCritical() << "Current state is nullptr " << __func__;
  }

  return response;
}
SetChannelStartSourceResponse DeviceEntityImpl::setChannelStartSource(SetChannelStartSourceRequest request) {
  SetChannelStartSourceResponse response{};

  if (_current_state != nullptr) {
    response = _current_state->setChannelStartSource(request);
  } else {
    qCritical() << "Current state is nullptr " << __func__;
  }

  return response;
}
SetChannelStartModeResponse DeviceEntityImpl::setChannelStartMode(SetChannelStartModeRequest request) {
  SetChannelStartModeResponse response{};

  if (_current_state != nullptr) {
    response = _current_state->setChannelStartMode(request);
  } else {
    qCritical() << "Current state is nullptr " << __func__;
  }

  return response;
}

GetChannelNameResponse DeviceEntityImpl::getChannelName(GetChannelNameRequest request) {
  GetChannelNameResponse response{};

  int channel_num = request.channel_num;
  if (channel_num >= 0 && channel_num < CHANNEL_COUNT) {
    if (_dto != nullptr) {
      auto &channels = _dto->channels;
      if (channel_num < channels.size()) {
        response.result = channels[channel_num].channel_name;
        response.error_code = SUCCESS;
      }
    }
  } else {
    response.error_code = INVALID_REQUEST;
  }

  return response;
}

SetChannelNameResponse DeviceEntityImpl::setChannelName(SetChannelNameRequest request) {
  SetChannelNameResponse response{};

  int channel_num = request.channel_num;
  auto channel_name = request.value;

  if (channel_num >= 0 && channel_num < CHANNEL_COUNT) {
    if (_dto != nullptr) {
      auto &channels = _dto->channels;
      if (channel_num < channels.size()) {
        channels[channel_num].channel_name = channel_name;
        response.result = channels[channel_num].channel_name;
        response.error_code = SUCCESS;
      }
    }
  } else {
    response.error_code = INVALID_REQUEST;
  }

  return response;
}
ErrorCode DeviceEntityImpl::loadDeviceDTO(const std::shared_ptr<DeviceEntityDTO> &dto) {
  ErrorCode result = OPERATION_INTERRUPTED;

  if (dto != nullptr) {
    _dto = dto;
    if (_current_state != nullptr) {
      result = _current_state->loadDeviceDTO(dto);
    }
  }

  return result;
}

std::shared_ptr<DeviceEntityDTO> DeviceEntityImpl::updateDeviceDTO() {
  return DeviceEntityState::updateDeviceDTO();
}

std::shared_ptr<DeviceEntityDTO> DeviceEntityImpl::getDeviceDTO() {
  return _dto;
}