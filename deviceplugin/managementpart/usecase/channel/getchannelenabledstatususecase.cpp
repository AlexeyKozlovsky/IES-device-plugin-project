#include "getchannelenabledstatususecase.h"

#include <QDebug>

GetChannelEnabledStatusUseCase::GetChannelEnabledStatusUseCase(const std::shared_ptr<DeviceEntity> &device_entity,
                                                               const std::shared_ptr<IDeviceEntityPoll> &device_entity_poll,
                                                               QObject *parent) :
    QObject(parent),
    _device_entity(device_entity),
    _device_entity_poll(device_entity_poll) {

}

GetChannelEnabledStatusUseCaseResponse GetChannelEnabledStatusUseCase::execute(GetChannelEnabledStatusUseCaseRequest request) {
  GetChannelEnabledStatusUseCaseResponse response{};

  auto channel_num = request.channel_num;

  if (_device_entity != nullptr) {

    GetChannelEnabledStatusRequest entity_request{channel_num};
    auto entity_response = _device_entity->getChannelsEnabledStatus(entity_request);

    response.error_code = entity_response.error_code;
    if (response.error_code == SUCCESS) {

      response.value = entity_response.result;
      if (_device_entity_poll != nullptr) {
        _device_entity_poll->channelEnabledStatusesPoll();
      } else {
        qCritical() << "Device entity poll is nullptr " << __func__;
      }
    } else {
      qCritical() << "Error code after set channel inverted status is not SUCCESS " << response.error_code << " "
                  << __func__;
    }
  }

  return response;
}


GetChannelEnabledStatusCommand::GetChannelEnabledStatusCommand(const std::shared_ptr<GetChannelEnabledStatusUseCase> &use_case):
    _use_case(use_case){

}

QVariant GetChannelEnabledStatusCommand::execute(QVariant request) {
  QVariant result;

  bool is_ok = false;
  auto channel_num = request.toInt(&is_ok);
  if (is_ok) {
    if (_use_case != nullptr) {
      GetChannelEnabledStatusUseCaseRequest uc_request{channel_num};
      auto uc_response = _use_case->execute(uc_request);
      if (uc_response.error_code == SUCCESS) {
        result = uc_response.value;
      } else {
        qCritical() << "Use case returned error in get channel delay use case " << __func__;
      }
    } else {
      qCritical() << "Unabled to parse QVariant request to int in get channel delay command " << __func__;
    }
  }

  return result;
}