<template>
    <div class="component-container">
        <div class="form-container">
            <form @submit.prevent>
                <div style="width:100%;" v-if="pins.length && remoteDevice.status === 'connected'">
                    <h2>Select Pins:</h2>
                    <div class="pin-selection-container">
                        <div v-for="pin in pins" :key="pin.pinNumber" class="pin-selection-item" :class="pin.status">
                            <input type="radio"  :id="pin.pinNumber" :value="pin.pinNumber" v-model="selectedPin" class="radio" />
                            <label :for="pin.id" class="label">{{`Pin: ${pin.pinNumber} : ${pin.status}`}}</label>
                        </div>
                    </div>
                <button @click="updatePinsStatus" class="button neutral">Update Pins' Status</button>
                    <button @click="fireSelectedPins" class="button">Fire selected pins</button>
                </div>
                <div v-if="pins.length <= 0 && remoteDevice.status === 'connected'" class="error">
                    <h2>Unable to display any pins. No pins have been enabled.</h2>
                    <button @click="updatePinsStatus" class="button enabled">Update Pins' Status</button>
                </div>
                <div v-if="remoteDevice.status !== 'connected'" class="error">
                    <h2>Unable to display any pins. Device is not connected.</h2>
                </div>
            </form>
        </div>
    </div>
</template>
<script>
import data from '../assets/data/db'

export default {
    name: 'EnabledPins',
    selectedPins: [],
    data(){
        return {
            pins: data.getEnabledPins(), //gets the pins froom db.js faila
            remoteDevice: data.getDevice(),
            selectedPin: null
        }
    },
    methods: {
        fireSelectedPins() {
            data.setPinStatus([this.selectedPin],'fired',  () => {
                this.$forceUpdate()
            })
            this.$forceUpdate()
        },
        updatePinsStatus() {
            data.fetchPinCurrentStatus(() => {
                this.$forceUpdate()
                this.pins = data.getEnabledPins()
                this.$forceUpdate()
            })
        },
    }

}
</script>