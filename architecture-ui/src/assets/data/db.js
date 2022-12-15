let storedData = {
    'remonteDevice': {
        'status': 'not-connected',
        'ipAddress': null
    },
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

const dataStore = {
    xhttpRequests: [],
    setPinStatus(pinNumbers, status, updatePinComponent){
        if(status == 'enabled') {
            this.enableSelectedPins(pinNumbers, updatePinComponent)
        }
        else if(status == 'disabled'){
            this.disableSelectedPins(pinNumbers, updatePinComponent)
        }
        else if(status == 'fired'){
            this.fireSelectedPins(pinNumbers, updatePinComponent)
        }
    },


    enableSelectedPins(pinNumbers, updatePinComponent) {
        pinNumbers.forEach((pinNumber) => {
            storedData.pins.forEach((pinObject) =>{
                if (pinObject.status !== 'enabled' && pinObject.pinNumber === pinNumber){
                    const url = new URL(`/pin/enable/${pinNumber}`, 'http://192.168.4.1')
                    let remoteOperationSucceed = true
                    let requestIndex = this.xhttpRequests.push(new XMLHttpRequest('GET', url, true))
                    requestIndex = requestIndex - 1
                    this.xhttpRequests[requestIndex].open('GET', url, true)
                    this.xhttpRequests[requestIndex].addEventListener('load', () =>{
                        const responseText =  this.xhttpRequests[requestIndex].responseText
                        const responseObject = JSON.parse(responseText) 
                        if (!('pinNumber' in responseObject) || !('status' in responseObject) || !(responseObject.pinNumber === pinNumber) || !(responseObject.status === "enabled"))
                        {
                            remoteOperationSucceed = false
                        }
                        if (remoteOperationSucceed)
                        {
                            pinObject.status = 'enabled'
                            updatePinComponent()
                        }
                    })
                    this.xhttpRequests[requestIndex].send()
                }
            })
        })
    },

    disableSelectedPins(pinNumbers, updatePinComponent) {
        pinNumbers.forEach((pinNumber) => {
            storedData.pins.forEach((pinObject) =>{
                if (pinObject.status !== 'disabled' && pinObject.pinNumber === pinNumber){
                    const url = new URL(`/pin/disable/${pinNumber}`, 'http://192.168.4.1')
                    let remoteOperationSucceed = true
                    let requestIndex = this.xhttpRequests.push(new XMLHttpRequest('GET', url, true))
                    requestIndex = requestIndex - 1
                    this.xhttpRequests[requestIndex].open('GET', url, true)
                    this.xhttpRequests[requestIndex].addEventListener('load', () =>{
                        const responseText =  this.xhttpRequests[requestIndex].responseText
                        const responseObject = JSON.parse(responseText) 
                        if (!('pinNumber' in responseObject) || !('status' in responseObject) || !(responseObject.pinNumber === pinNumber) || !(responseObject.status === "disabled"))
                        {
                            remoteOperationSucceed = false
                        }
                        if (remoteOperationSucceed)
                        {
                            pinObject.status = 'disabled'
                            updatePinComponent()

                        }
                        
                    })
                    this.xhttpRequests[requestIndex].send()
                }
            })
        })
    },
    
    fireSelectedPins(pinNumbers, updatePinComponent) {
        pinNumbers.forEach((pinNumber) => {
            storedData.pins.forEach((pinObject) =>{
                if (pinObject.status !== 'fired' && pinObject.status !== 'disabled' && pinObject.pinNumber === pinNumber){
                    const url = new URL(`/pin/fire/${pinNumber}`, 'http://192.168.4.1')
                    let remoteOperationSucceed = true
                    let requestIndex = this.xhttpRequests.push(new XMLHttpRequest('GET', url, true))
                    requestIndex = requestIndex - 1
                    this.xhttpRequests[requestIndex].open('GET', url, true)
                    this.xhttpRequests[requestIndex].addEventListener('load', () =>{
                        const responseText =  this.xhttpRequests[requestIndex].responseText
                        const responseObject = JSON.parse(responseText) 
                        if (!('pinNumber' in responseObject) || !('status' in responseObject) || !(responseObject.pinNumber === pinNumber) || !(responseObject.status === "fired"))
                        {
                            remoteOperationSucceed = false
                        }
                        if (remoteOperationSucceed)
                        {
                            pinObject.status = 'fired'
                            updatePinComponent()
                        }
                    })
                    this.xhttpRequests[requestIndex].send()
                }
            })
        })
    },

    fetchPinCurrentStatus(updatePinComponent) {
        const url = new URL(`/device/pins/status`, 'http://192.168.4.1')
        let requestIndex = this.xhttpRequests.push(new XMLHttpRequest('GET', url, true))
        requestIndex = requestIndex - 1
        this.xhttpRequests[requestIndex].open('GET', url, true)
        this.xhttpRequests[requestIndex].addEventListener('load', () =>{
            const responseText =  this.xhttpRequests[requestIndex].responseText
            const responseObject = JSON.parse(responseText)
            const updatedPins = responseObject.pins
            updatedPins.forEach((updatedPin) => {
                storedData.pins.forEach((pinObject) =>{
                    if (pinObject.pinNumber === updatedPin.pinNumber && pinObject.status !== updatedPin.status) {
                        pinObject.status = updatedPin.status
                    }
                })
            }) 
            updatePinComponent()
        })
        this.xhttpRequests[requestIndex].send()
    },

    getEnabledPins(){
        return storedData.pins.filter((pin) => pin.status == 'enabled')
    },
    getPins() {
        return storedData.pins
    },
    getDevice() {
        return storedData.device;
    } 
}
export default dataStore