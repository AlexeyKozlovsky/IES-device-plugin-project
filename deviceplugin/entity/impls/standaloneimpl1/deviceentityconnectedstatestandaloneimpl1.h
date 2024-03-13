#ifndef CPSDEVICESTANDALONEPLUGIN_DEVICEPLUGIN_ENTITY_IMPLS_STANDALONEIMPL1_DEVICEENTITYCONNECTEDSTATESTANDALONEIMPL1_H_
#define CPSDEVICESTANDALONEPLUGIN_DEVICEPLUGIN_ENTITY_IMPLS_STANDALONEIMPL1_DEVICEENTITYCONNECTEDSTATESTANDALONEIMPL1_H_

#include <memory>

#include "deviceplugin/entity/deviceentity.h"


class DeviceEntityConnectedStateStandaloneImpl1: public DeviceEntityState {
 public:
  explicit DeviceEntityConnectedStateStandaloneImpl1(const std::shared_ptr<DeviceEntity> &device_entity,
                                                     const std::shared_ptr<DeviceEntityRegCard> &reg_card,
                                                     const std::shared_ptr<DeviceEntityRegCard> &postponed_reg_card);

    GetInnerStartWidthResponse getInnerStartWidth(GetInnerStartWidthRequest request) override;

    GetSyncModuleStatusesResponse getSyncModuleStatuses(GetSyncModuleStatusesRequest request) override;
  GetSFPParametersResponse getSFPParameters(GetSFPParametersRequest request) override;
  GetChannelWidthResponse getChannelsWidth(GetChannelWidthRequest request) override;

    GetInnerStartEnabledStatusResponse getInnerStartEnabledStatus(GetInnerStartEnabledStatusRequest request) override;

    GetChannelEnabledStatusResponse getChannelsEnabledStatus(GetChannelEnabledStatusRequest request) override;
  GetChannelInvertedStatusResponse getChannelsInvertedStatus(GetChannelInvertedStatusRequest request) override;
  GetChannelStartModeResponse getChannelsStartMode(GetChannelStartModeRequest request) override;
  GetChannelStartSourceResponse getChannelsStartSource(GetChannelStartSourceRequest request) override;

  GetChannelDelayResponse getChannelsDelay(GetChannelDelayRequest request) override;
  int getChannelCount() override;

  SetChannelDelayResponse setChannelDelay(SetChannelDelayRequest request) override;
  SetChannelWidthResponse setChannelWidth(SetChannelWidthRequest request) override;
  SetChannelEnabledStatusResponse setChannelEnabledStatus(SetChannelEnabledStatusRequest request) override;
  SetChannelInvertedStatusResponse setChannelInvertedStatus(SetChannelInvertedStatusRequest request) override;
  SetChannelStartSourceResponse setChannelStartSource(SetChannelStartSourceRequest request) override;
  SetChannelStartModeResponse setChannelStartMode(SetChannelStartModeRequest request) override;

  ErrorCode loadDeviceDTO(const std::shared_ptr<DeviceEntityDTO> &dto) override;
  std::shared_ptr<DeviceEntityDTO> updateDeviceDTO() override;

 private:
  std::shared_ptr<DeviceEntityRegCard> _reg_card = nullptr;
  std::shared_ptr<DeviceEntityRegCard> _postponed_reg_card = nullptr;
  std::shared_ptr<DeviceEntity> _device_entity = nullptr;
};

#endif //CPSDEVICESTANDALONEPLUGIN_DEVICEPLUGIN_ENTITY_IMPLS_STANDALONEIMPL1_DEVICEENTITYCONNECTEDSTATESTANDALONEIMPL1_H_
