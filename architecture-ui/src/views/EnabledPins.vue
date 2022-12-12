<template>
    <form @submit.prevent>
        <div v-if="pins.length">
            <h2>Select Pins:</h2>
            <div class="pin-selection-container">
                <div v-for="pin in pins" :key="pin.id" class="pin-selection-item" :class="pin.status">
                    <input type="checkbox"  :id="pin.id" :value="pin.id" v-model="selectedPins" class="checkbox" />
                    <label :for="pin.id" class="label">{{ pin.name }}: {{pin.status}}</label>
                </div>
            </div>
            <button @click="fireSelectedPins" class="button">Fire selected pins</button>
        </div>
        <div v-else class="error">
            <h2>Unable to display any pins since no pins have been enabled</h2>
        </div>
    



    </form>
</template>
<script>
import data from '../assets/data/db'

export default {
    name: 'EnabledPins',
    selectedPins: [],
    data(){
        return {
            pins: data.getEnabledPins(), //gets the pins froom db.js faila
            selectedPins: []
        }
    },
    methods: {
        fireSelectedPins() {
            data.setPinStatus(this.selectedPins,'fired')
            this.$forceUpdate()
        },
    }

}
</script>
<style>
.error{
    width: 400px;
}
</style>