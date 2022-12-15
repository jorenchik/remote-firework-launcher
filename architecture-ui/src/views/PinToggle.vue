<template>
  <div class="container">


    <form @submit.prevent>
      <h2>Select Pins:</h2>
      <div class="pin-selection-container">
        <div v-for="pin in pins" :key="pin.pinNumber" class="pin-selection-item" :class="pin.status">
            <input type="checkbox"  :id="pin.pinNumber" :value="pin.pinNumber" v-model="selectedPins" class="checkbox" />
            <label :for="pin.id" class="label">{{`Pin: ${pin.pinNumber} : ${pin.status}`}}</label>
        </div>
      </div>
    

      <button @click="enableSelectedPins" class="button enabled">Enable Selected Pins</button>
      <button @click="disableSelectedPins" class="button disabled">Disable Selected Pins</button>
    </form>
  </div>

</template>


<script>
import { computed } from '@vue/reactivity';
import data from '../assets/data/db'



export default {
  name: 'PinToggle',
  data() {
    return {
      pins: data.getPins(), //gets the pins froom db.js faila
      selectedPins: []
    };
  },
  methods: {
    enableSelectedPins() {
      data.setPinStatus(this.selectedPins,'enabled')
      this.$forceUpdate()
    },
    disableSelectedPins() {
      data.setPinStatus(this.selectedPins,'disabled')
      this.$forceUpdate()
    }

  }
};
</script>

