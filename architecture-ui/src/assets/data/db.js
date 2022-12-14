let storedData = {
    'pins': [
        {
            "pinNumber": "13",
            "status": "disabled"
        },
        {
            "pinNumber": "16",
            "status": "disabled"
        },
        {
            "pinNumber": "17",
            "status": "disabled"
        },
        {
            "pinNumber": "18",
            "status": "disabled"
        },
        {
            "pinNumber": "19",
            "status": "disabled"
        },
        {
            "pinNumber": "21",
            "status": "disabled"
        },
        {
            "pinNumber": "22",
            "status": "disabled"
        },
        {
            "pinNumber": "23",
            "status": "disabled"
        },
        {
            "pinNumber": "25",
            "status": "disabled"
        },
        {
            "pinNumber": "26",
            "status": "disabled"
        },
        {
            "pinNumber": "27",
            "status": "disabled"
        },
        {
            "pinNumber": "32",
            "status": "disabled"
        },
        {
            "pinNumber": "33",
            "status": "disabled"
        }
    ],
    'device': {
        'status': 'not-ready'
    }
}

// console.log(process.env.VUE_APP_ESP_CONNECTION);

const dataStore = {
    setPinStatus(pinNumbers, status){
        if(status == 'enabled') {
            this.enableSelectedPins(pinNumbers)
        }
        else if(status == 'disabled'){
            this.disableSelectedPins(pinNumbers)
        }
        else if(status == 'fired'){
            this.fireSelectedPins(pinNumbers)
        }
    },


    enableSelectedPins(pinNumbers) {
        pinNumbers.forEach((pinNumber) => {
            storedData.pins.forEach((pinObject) =>{
                if (pinObject.status !== 'enabled' && pinObject.pinNumber === pinNumber){
                    pinObject.status = 'enabled'
                }
            })
        })
    },

    disableSelectedPins(pinNumbers) {
        pinNumbers.forEach((pinNumber) => {
            storedData.pins.forEach((pinObject) =>{
                if (pinObject.status !== 'disabled' && pinObject.pinNumber === pinNumber){
                    pinObject.status = 'disabled'
                }
            })
        })
    },
    fireSelectedPins(pinNumbers) {
        pinNumbers.forEach((pinNumber) => {
            storedData.pins.forEach((pinObject) =>{
                if (pinObject.status !== 'fired' && pinObject.pinNumber === pinNumber){
                    pinObject.status = 'fired'
                }
            })
        })
    },
    getEnabledPins(){
        return storedData.pins.filter((pin) => pin.status == 'enabled')
    },
    getPins() {
        return storedData.pins
    }
}
export default dataStore