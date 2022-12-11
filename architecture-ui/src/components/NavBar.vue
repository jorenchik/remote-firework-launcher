<template>
    <nav>
      <router-link to="/">Home</router-link>
      <router-link :to="{name: 'PinToggle'}">Toggle pins</router-link>
      <router-link :to="{name: 'enabled'}">Enabled pins</router-link>
    </nav>
</template>
<script>
export default {
    
}
</script>
<style >
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #42b983;
  
}

nav {
  padding: 30px;
}

nav a {
  font-weight: bold;
  color: #23001e;
  text-decoration: none;
  padding: 10px;
  margin: 5px;
  border-radius: 4px;
}

nav a.router-link-exact-active {
  color: white;
  background-color: #23001e;
}
</style>