/*
 *  RPLIDAR SDK
 *
 *  Copyright (c) 2009 - 2014 RoboPeak Team
 *  http://www.robopeak.com
 *  Copyright (c) 2014 - 2019 Shanghai Slamtec Co., Ltd.
 *  http://www.slamtec.com
 *
 */
/*
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, 
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice, 
 *    this list of conditions and the following disclaimer in the documentation 
 *    and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#pragma once

namespace rp { namespace standalone{ namespace rplidar {
    class RPlidarDriverImplCommon : public RPlidarDriver
{
public:
    enum {
        RPLIDAR_TOF_MINUM_MAJOR_ID = 5,
    };

    virtual bool isConnected();     
    virtual u_result reset(_u32 timeout = DEFAULT_TIMEOUT);
    virtual u_result clearNetSerialRxCache();
    virtual u_result getAllSupportedScanModes(std::vector<RplidarScanMode>& outModes, _u32 timeoutInMs = DEFAULT_TIMEOUT);
    virtual u_result getTypicalScanMode(_u16& outMode, _u32 timeoutInMs = DEFAULT_TIMEOUT);
    virtual u_result getDeviceLevel(_u8& level, _u32 timeoutInMs= DEFAULT_TIMEOUT);
    virtual u_result checkSupportConfigCommands(bool& outSupport, _u32 timeoutInMs = DEFAULT_TIMEOUT);

    virtual u_result getScanModeCount(_u16& modeCount, _u32 timeoutInMs = DEFAULT_TIMEOUT);
    virtual u_result getLidarSampleDuration(float& sampleDurationRes, _u16 scanModeID, _u32 timeoutInMs = DEFAULT_TIMEOUT);
    virtual u_result getMaxDistance(float &maxDistance, _u16 scanModeID, _u32 timeoutInMs = DEFAULT_TIMEOUT);
    virtual u_result getScanModeAnsType(_u8 &ansType, _u16 scanModeID, _u32 timeoutInMs = DEFAULT_TIMEOUT);
    virtual u_result getScanModeName(char* modeName, _u16 scanModeID, _u32 timeoutInMs = DEFAULT_TIMEOUT);
    virtual u_result setLidarConf(_u32 type, const void* payload, size_t payloadSize, _u32 timeout = DEFAULT_TIMEOUT);
    virtual u_result getLidarConf(_u32 type, std::vector<_u8> &outputBuf, const std::vector<_u8> &reserve = std::vector<_u8>(), _u32 timeout = DEFAULT_TIMEOUT);

    virtual u_result startScan(bool force, bool useTypicalScan, _u32 options = 0, RplidarScanMode* outUsedScanMode = NULL);
    virtual u_result startScanExpress(bool force, _u16 scanMode, _u32 options = 0, RplidarScanMode* outUsedScanMode = NULL, _u32 timeout = DEFAULT_TIMEOUT);


    virtual u_result getHealth(rplidar_response_device_health_t & health, _u32 timeout = DEFAULT_TIMEOUT);
    virtual u_result getDeviceInfo(rplidar_response_device_info_t & info, _u32 timeout = DEFAULT_TIMEOUT);
    virtual u_result getDeviceMacAddr(_u8* macAddrArray, _u32 timeoutInMs = DEFAULT_TIMEOUT);
    virtual u_result setLidarDetectMode(rplidar_device_detect_mode_t mode, _u32 timeoutInMs = DEFAULT_TIMEOUT);
    virtual u_result getLidarDetectMode(rplidar_device_detect_mode_t& mode, _u32 timeoutInMs = DEFAULT_TIMEOUT);
    virtual u_result checkIfTofLidar(bool & isTofLidar, _u32 timeout = DEFAULT_TIMEOUT);
    virtual u_result setLidarIpConf(const rplidar_ip_conf_t& conf, _u32 timeout = DEFAULT_TIMEOUT);
    virtual u_result getSampleDuration_uS(rplidar_response_sample_rate_t & rateInfo, _u32 timeout = DEFAULT_TIMEOUT);
    virtual u_result setMotorPWM(_u16 pwm);
    virtual u_result setLidarSpinSpeed(_u16 rpm, _u32 timeout = DEFAULT_TIMEOUT);
    virtual u_result startMotor();
    virtual u_result stopMotor();
    virtual u_result checkMotorCtrlSupport(bool & support, _u32 timeout = DEFAULT_TIMEOUT);
    virtual u_result getFrequency(bool inExpressMode, size_t count, float & frequency, bool & is4kmode);
    virtual u_result getFrequency(const RplidarScanMode& scanMode, size_t count, float & frequency);
    virtual u_result startScanNormal(bool force, _u32 timeout = DEFAULT_TIMEOUT);
    virtual u_result checkExpressScanSupported(bool & support, _u32 timeout = DEFAULT_TIMEOUT);
    virtual u_result stop(_u32 timeout = DEFAULT_TIMEOUT);
    virtual u_result grabScanData(rplidar_response_measurement_node_t * nodebuffer, size_t & count, _u32 timeout = DEFAULT_TIMEOUT);
    virtual u_result grabScanDataHq(rplidar_response_measurement_node_hq_t * nodebuffer, size_t & count, _u32 timeout = DEFAULT_TIMEOUT);
    virtual u_result ascendScanData(rplidar_response_measurement_node_t * nodebuffer, size_t count);
    virtual u_result ascendScanData(rplidar_response_measurement_node_hq_t * nodebuffer, size_t count);
    virtual u_result getScanDataWithInterval(rplidar_response_measurement_node_t * nodebuffer, size_t & count);
    virtual u_result getScanDataWithIntervalHq(rplidar_response_measurement_node_hq_t * nodebuffer, size_t & count);

protected:

    virtual u_result _sendCommand(_u8 cmd, const void * payload = NULL, size_t payloadsize = 0);
    void     _disableDataGrabbing();

    virtual u_result _waitResponseHeader(rplidar_ans_header_t * header, _u32 timeout = DEFAULT_TIMEOUT);
    virtual u_result _cacheScanData();
    virtual u_result _waitScanData(rplidar_response_measurement_node_t * nodebuffer, size_t & count, _u32 timeout = DEFAULT_TIMEOUT);
    virtual u_result _waitNode(rplidar_response_measurement_node_t * node, _u32 timeout = DEFAULT_TIMEOUT);
    virtual u_result  _cacheCapsuledScanData();
    virtual u_result _waitCapsuledNode(rplidar_response_capsule_measurement_nodes_t & node, _u32 timeout = DEFAULT_TIMEOUT);
    virtual int _getSyncBitByAngle(const int current_angle_q16, const int angleInc_q16);
    virtual void     _capsuleToNormal(const rplidar_response_capsule_measurement_nodes_t & capsule, rplidar_response_measurement_node_hq_t *nodebuffer, size_t &nodeCount);
    virtual void     _dense_capsuleToNormal(const rplidar_response_capsule_measurement_nodes_t & capsule, rplidar_response_measurement_node_hq_t *nodebuffer, size_t &nodeCount);
    
    //FW1.23
    virtual u_result  _cacheUltraCapsuledScanData();
    virtual u_result _waitUltraCapsuledNode(rplidar_response_ultra_capsule_measurement_nodes_t & node, _u32 timeout = DEFAULT_TIMEOUT);
    virtual void     _ultraCapsuleToNormal(const rplidar_response_ultra_capsule_measurement_nodes_t & capsule, rplidar_response_measurement_node_hq_t *nodebuffer, size_t &nodeCount);

    virtual u_result  _cacheHqScanData();
    virtual u_result _waitHqNode(rplidar_response_hq_capsule_measurement_nodes_t & node, _u32 timeout = DEFAULT_TIMEOUT);
    virtual void     _HqToNormal(const rplidar_response_hq_capsule_measurement_nodes_t & node_hq, rplidar_response_measurement_node_hq_t *nodebuffer, size_t &nodeCount);

    bool     _isConnected; 
    bool     _isScanning;
    bool     _isSupportingMotorCtrl;
    bool     _isTofLidar;
    rplidar_response_measurement_node_hq_t   _cached_scan_node_hq_buf[8192];
    size_t                                   _cached_scan_node_hq_count;

    rplidar_response_measurement_node_hq_t   _cached_scan_node_hq_buf_for_interval_retrieve[8192];
    size_t                                   _cached_scan_node_hq_count_for_interval_retrieve;

    _u16                    _cached_sampleduration_std;
    _u16                    _cached_sampleduration_express;
    _u8                     _cached_express_flag;
    float                   _cached_current_us_per_sample;

    rplidar_response_capsule_measurement_nodes_t _cached_previous_capsuledata;
    rplidar_response_dense_capsule_measurement_nodes_t _cached_previous_dense_capsuledata;
    rplidar_response_ultra_capsule_measurement_nodes_t _cached_previous_ultracapsuledata;
    rplidar_response_hq_capsule_measurement_nodes_t _cached_previous_Hqdata;
    bool                                         _is_previous_capsuledataRdy;
    bool                                         _is_previous_HqdataRdy;
    bool                                         _syncBit_is_finded;

	

    rp::hal::Locker         _lock;
    rp::hal::Event          _dataEvt;
    rp::hal::Thread _cachethread;

protected:
    RPlidarDriverImplCommon();
    virtual ~RPlidarDriverImplCommon() {}
};
}}}