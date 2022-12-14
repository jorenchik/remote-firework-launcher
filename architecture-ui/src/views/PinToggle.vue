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
  display:inline-flex;
  background: #8F6593;
  width: 150px;
  padding: 20px;
  border-radius: 20px;
  margin-bottom: 10px;
}

.pin-selection-item {
  padding: 3px 10px;
  margin: 3px auto;
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

.checkbox {
/* -webkit-appearance: none; */

border: 1px solid #000;
width: 15px;
height: 15px;
border-radius: 2px;
margin-right: 10px;
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



