<template>
   <NavBar/> 

   <router-view/>

</template>

<script>
import NavBar from './components/NavBar.vue'
export default {
  name: 'Home',
  components: { NavBar},

}

</script>

<style>
body {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  text-align: center;
  color: #7353ba;
  background: #23001E; 
}

nav {
  padding: 30px;
}

nav a {
  font-weight: bold;
  color: #7353ba;
}

nav a.router-link-exact-active {
  color: #42b983;
}
</style>
