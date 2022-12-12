let storedData = [
    { id: 1, name: "Pin 1", status: 'disabled'},
    { id: 2, name: "Pin 2", status: 'disabled' },
    { id: 3, name: "Pin 3", status: 'disabled' },
    { id: 4, name: "Pin 4", status: 'disabled' },
    { id: 5, name: "Pin 5", status: 'disabled' },
    { id: 6, name: "Pin 6", status: 'disabled' },
    { id: 7, name: "Pin 7", status: 'disabled' },
    { id: 8, name: "Pin 8", status: 'disabled' }
 ]

const dataStore = {
    getUserData() {
        return storedData
    },
    setPinStatus(ids, status){
        if(status == 'enabled'){
            this.enableSelectedPins(ids)
        }
        else if(status == 'disabled'){
            this.disableSelectedPins(ids)
        }
        else if(status == 'fired'){
            this.fireSelectedPins(ids)
        }
    },


    enableSelectedPins(ids) {
    // send request to enable selected pins on ESP8266
        ids.forEach((id) => {
            storedData.forEach((pinObject) =>{
                if (pinObject.status !== 'enabled' && pinObject.id === id && pinObject.status !== 'fired'){
                    pinObject.status = 'enabled'
                }

            })
        })
    },

    disableSelectedPins(ids) {
        ids.forEach((id) => {
            storedData.forEach((pinObject) =>{
                if (pinObject.status !== 'disabled' && pinObject.id === id && pinObject.status !== 'fired'){
                    pinObject.status = 'disabled'
                }
            })
        })
    },
    fireSelectedPins(ids) {
        ids.forEach((id) => {
            storedData.forEach((pinObject) =>{
                if (pinObject.status !== 'fired' && pinObject.id === id ){
                    pinObject.status = 'fired'
                }
            })
        })
    },
    getEnabledPins(){
        return storedData.filter((pin) => pin.status == 'enabled')
    }
}
export default dataStore