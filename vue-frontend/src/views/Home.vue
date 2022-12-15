<template>
  <div class="component-container">
    <div>
      <h1>Home</h1>
      <p>Welcome to the ESP32 remote control app!</p>
      <input class="text-input" v-model="ipAddress">
      <input type="button" class="button enable" @click="establishConnection" value="Submit">
      <p v-if="!addressValidated">Invalid ip address...</p>
    </div>
  </div>
</template>

<script>
import data from '../assets/data/db.js'

export default {
  name: 'Home',
  data() {
    return {
      ipAddress: null,
      addressValidated: true
    }
  },
  methods: {
    establishConnection() {
      const ipAddressValidateRegEx = /^((25[0-5]|(2[0-4]|1\d|[1-9]|)\d)\.?\b){4}$/
      if(!this.ipAddress.match(ipAddressValidateRegEx)) {
        this.addressValidated = false
      } else {
        this.addressValidated = true
        data.setDeviceIpAddress(this.ipAddress)
      }
      this.$forceUpdate()
      return;
    }
  }
}
</script>