<template>
  <div class="component-container">
    <div>
      <h1>Home</h1>
      <p>Welcome to the ESP32 remote control app!</p>
      <p>Current status: {{device && device.status === 'connected' ? 'connected' : 'not connected'}}</p>
      <input v-if="!device || device.status !== 'connected'" class="text-input" v-model="ipAddress">
      <input v-if="!device || device.status !== 'connected'" type="button" class="button enable" @click="establishConnection" value="Connect">
      <input v-if="device && device.status === 'connected'" type="button" class="button enable" @click="breakConnection" value="Disconnect">
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
      ipAddress: '192.168.4.1',
      addressValidated: true,
      device: data.getDevice()
    }
  },
  methods: {
    establishConnection() {
      if (this.device && this.device.status === 'connected')
      {
        return;
      }
      const ipAddressValidateRegEx = /^((25[0-5]|(2[0-4]|1\d|[1-9]|)\d)\.?\b){4}$/
      if(!this.ipAddress.match(ipAddressValidateRegEx)) {
        this.addressValidated = false
      } else {
        this.addressValidated = true
        data.setDeviceIpAddress(this.ipAddress, () => {this.$forceUpdate()})
        this.device = data.getDevice()
      }
      return;
    },
    breakConnection() {
      if (this.device && this.device.status !== 'connected')
      {
        return;
      }
      data.disconnectDevice()
      this.device = data.getDevice()
      this.$forceUpdate();

      return;
    }
  }
}
</script>