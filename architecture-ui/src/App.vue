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
  /* Document styles */
  body {
    font-family: Avenir, Helvetica, Arial, sans-serif;
    -webkit-font-smoothing: antialiased;
    -moz-osx-font-smoothing: grayscale;
    text-align: center;
    color: #7353ba;
    background: #23001E; 
  }
  /* Navbar */
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
  form {
    display: flex;
    flex-direction: column;
    align-items: center;
  }

  /* Form */
  label {
    font-weight: bold;
  }
  .pin-selection-container {
    flex-direction: column;
    align-items: center;
    display: flex;
    background: #8F6593;
    width: 80%;
    padding: 20px;
    border-radius: 20px;
    margin-bottom: 10px;
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
  .error{
      width: 400px;
  }
  /* Buttons */
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
