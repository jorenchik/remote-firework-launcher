<template>
  <div class="component-container">
    <div class="form-container">
      <form v-if="remoteDevice.status === 'connected'" @submit.prevent>
        <h2>Select Pins:</h2>
        <div style="width: 100%;" class="pin-selection-container">
          <div v-for="pin in pins" :key="pin.pinNumber" class="pin-selection-item" :class="pin.status">
            <input type="checkbox" label="Default gateway IP address" :id="pin.pinNumber" :value="pin.pinNumber" v-model="selectedPins" class="checkbox" />
            <label :for="pin.id" class="label">{{`Pin: ${pin.pinNumber} : ${pin.status}`}}</label>
          </div>
        </div>
        <button @click="updatePinsStatus" class="button neutral">Update Pins' Status</button>
        <button @click="enableSelectedPins" class="button enabled">Enable Selected Pins</button>
        <button @click="disableSelectedPins" class="button disabled">Disable Selected Pins</button>
      </form>
      <div v-if="remoteDevice.status !== 'connected'" class="error">
        <h2>Unable to display any pins. Device is not connected.</h2>
      </div>
    </div>
  </div>
</template>

<script>
import data from '../assets/data/db'

export default {
  name: 'PinToggle',
  data() {
    return {
      pins: data.getPins(), //gets the pins froom db.js faila
      remoteDevice: data.getDevice(),
      selectedPins: []
    };
  },
  methods: {
    enableSelectedPins() {
      data.setPinStatus(this.selectedPins,'enabled', () => {
        this.$forceUpdate()
      })
    },
    disableSelectedPins() {
      data.setPinStatus(this.selectedPins,'disabled', () => {
        this.$forceUpdate()
      })
      this.$forceUpdate()
    },
    updatePinsStatus() {
      data.fetchPinCurrentStatus(() => {
        this.$forceUpdate()
      })
    }
  }
};
</script>

