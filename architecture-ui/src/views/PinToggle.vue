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
<style>

form {
  display: flex;
  flex-direction: column;
  align-items: center;
}
label {
  font-weight: bold;
}
.pin-selection-container {
  flex-direction: column;
  align-items: center;
  display: flex;
  background: #8F6593;
  width: 60%;
  padding: 20px;
  border-radius: 20px;
  margin-bottom: 10px;
}

@media (min-width: 768px) {
  .pin-selection-container {
    width: 20rem;
  }
}

.pin-selection-item {
  padding-top: .5rem;
  padding-bottom: .5rem;
  text-transform: uppercase;
  display: flex;
  justify-content: center;
  place-content: center;
  border-radius: 5px;
  font-size: 14px;
  margin-bottom: 10px;
  background-color: #8F6593;
  width: 90%;
}
.button {
  background-color: #008577;
  border-radius: 7px;
  padding: 10px 15px;
  margin: 5px auto;
  color: #23001E;
  font-weight: bold;
  display: flex;
}
.checkbox, .radio {
  border: 1px solid #000;
  width: 15px;
  height: 15px;
  border-radius: 2px;
  margin: 0 1rem 0 0;
  cursor: pointer;
}
.enabled{
  background: #42b983;
  color: black;
}
.disabled{
  background: #7353ba;
  color: white;
}
.fired{
  background: #23001E;
  color: white;
}


</style>



