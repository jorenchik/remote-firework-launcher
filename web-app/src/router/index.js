import { createRouter, createWebHashHistory } from 'vue-router'
import Home from '../views/Home.vue'
import Enabled from '../views/EnabledPins.vue'
import PinToggle from '../views/PinToggle.vue'

const routes = [
  {
    path: '/',
    name: 'home',
    component: Home
  },
  {
    path: '/PinToggle',
    name: 'PinToggle',
    component: PinToggle
  },
  {
    path: '/enabled',
    name: 'enabled',
    component: Enabled
  }
]

const router = createRouter({
  history: createWebHashHistory(process.env.BASE_URL),
  routes
})

export default router
