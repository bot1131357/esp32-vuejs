<script setup>
import { reactive, ref } from 'vue'

const message = ref('This is the play page!')
let id = 0 // give each todo a unique id

const newTodo = ref('')
const todos = ref([
  { id: id++, text: 'Learn HTML' },
  { id: id++, text: 'Learn JavaScript' },
  { id: id++, text: 'Learn Vue' }
])

function addTodo() {
  todos.value.push({ id: id++, text: newTodo.value })
  newTodo.value = ''
}

function removeTodo(todo) {
  console.log('removeTodo', todo)
  todos.value = todos.value.filter((t) => t !== todo)
}
</script>

<template>
  <div class="play">
    <h1>{{ message }}</h1>

    <div>
      <p>Item in list: {{ todos.length }}</p>
      <form @submit.prevent="addTodo">
        <input v-model="newTodo" required placeholder="New todo" @change="validateInput">
        <button :disabled="newTodo.length==0">➕</button>
      </form>
      <ul>
        <li v-for="todo in todos" :key="todo.id">
          <span class="todo"><div>{{ todo.text }}</div> <button @click="removeTodo(todo)">❎</button></span>
        </li>
      </ul>
    </div>
  </div>
</template>

<style scoped>
.play {
  max-width: 800px;
}

input {
  border-radius: 3px;
  margin: 5px 0;
  padding: 5px;
}
button {
  margin: 5px 0;
  padding: 5px;
  border: none;
  background: none;
  text-shadow: 1px 1px #0004;
  font-size: x-small;  
  cursor: pointer;
}

ul {
  list-style-type: none;
  padding: 0; /* Remove padding */
  margin: 0; /* Remove margins */
}

li {
  margin: 10px 0px ;
  text-shadow: 1px 1px #0004;
  border: solid 1px #9999;
  border-radius: 3px;
  background: #9993;
}

.todo {
  display: flex;
  padding: 15px;
  justify-content: space-between;
  /* background: #aaa; */
  /* border: solid 1px #ccc; */
}
</style>