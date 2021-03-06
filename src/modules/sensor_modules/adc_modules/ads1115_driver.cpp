#include "ads1115_driver.h"



void ADS1115Driver::_getData() {

    if (adc_.isBusy()) return;

    adcCounter_++;

    //adc_.readADC(currentPin_);

    voltageTimestampFifo_[currentPin_].placeFront(micros(), true);
    voltageFifo_[currentPin_].placeFront(adc_.toVoltage(adc_.getValue()), true);

    currentPin_++;
    if (currentPin_ >= 4) currentPin_ = 0;

    adc_.requestADC(currentPin_);

}


void ADS1115Driver::thread() {

    if (block_) return;

    loopCounter_++;


    if (moduleStatus_ == eModuleStatus_t::eModuleStatus_Running) {

        _getData();

    } else if (moduleStatus_ == eModuleStatus_t::eModuleStatus_NotStarted || moduleStatus_ == eModuleStatus_t::eModuleStatus_RestartAttempt) {
        
        init();

    } else if (false/*moduleStatus_ == eModuleStatus_t::MODULE_CALIBRATING*/) {

        //################## Following is Temporary #################
        

        moduleStatus_ = eModuleStatus_t::eModuleStatus_Running; 

    } else { //This section is for device failure or a wierd mode that should not be set, therefore assume failure

        moduleStatus_ = eModuleStatus_t::eModuleStatus_Failure;
        block_ = true;
        loopRate_ = 0;

    }



    if (_rateCalcInterval.isTimeToRun()) {
        loopRate_ = loopCounter_;
        adcRate_ = adcCounter_;
        adcCounter_ = 0;
        loopCounter_ = 0;
    }

}



void ADS1115Driver::init() {

    int startCode = adc_.begin();

    if (startCode > 0) {

        adc_.setMode(1);
        adc_.setGain(1);
        adc_.setDataRate(7);
        adc_.requestADC(0);

        lastMeasurement_ = micros();

        moduleStatus_ = eModuleStatus_t::eModuleStatus_Running;

        Serial.println("ADC Start Success.");

    } else {
        moduleStatus_ = eModuleStatus_t::eModuleStatus_RestartAttempt; 
        Serial.println("ADC Start Fail. Code: " + String(startCode));
    }

    startAttempts_++;

    if (startAttempts_ >= 5 && moduleStatus_ == eModuleStatus_t::eModuleStatus_RestartAttempt) moduleStatus_ = eModuleStatus_t::eModuleStatus_Failure;

}
