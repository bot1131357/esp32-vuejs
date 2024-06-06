# Example Vue.js app deployment on ESP32

If you just want to get it running, you can start from Step 1.  
See Step 0 if you want to create from scratch.

0) [Starting from scratch)](#from-scratch)
1) [Cloning from repo)](#from-repo)
2) [Deployment](#deploy-vue-app)


# From scratch
## Create a Vue project
```
npm init vue vue-app
cd vue-app
npm install
```


## Build config 
Since SPIFFS runs on a flat file system, we want the output files to be placed in a flat directory structure. Add the following option to `vite.config.js`:
```
	build: { 
		assetsDir: './'
	},
```


## Cleanup (For a clean project)
Remove files in these dir:
- `/assets`
- `/components`

Remove references to them in:
- main.js
- App.vue
- HomeView.vue
- AboutView.vue


## Added PlayView.vue 
For testing Vue.js features 
The Todo list example taken from (https://vuejs.org/tutorial/##step-8)


# From repo
## Clone project
```
git clone https://github.com/bot1131357/esp32-vuejs
```


## Install required packages
```
cd vue-app
npm install
```


# Deploy Vue App
## Build project
```
npm run build
```


## Using the dist files in your Platform.io project
Copy files from `/esp32-vuejs/dist` to `/platform_io/data` in your platform.io project.  
~~Since SPIFFS runs on a flat file system, move the files from `/platform_io/data/assets` to `/platform_io/data` and delete the dir.~~


## ~~Update references~~
~~Since we no longer use the `/platform_io/data/assets` dir, remove the prefixes `/assets/` and `assets/` from the references in the generated files.~~


## Flashing ESP32
Upload filesystem image, and upload ESP32 program. Reset, and your Vue.js page is now served at your ESP32's IP address.


## Thoughts
The output files amount to 86.5kB. With lazy loading, I'm loading 87.5kB (89.9kB total) - pretty significant for an ESP32. I could probably do with much less with just pure JS.
I suppose it comes down to how much your app benefits from Vue.js. 🙂


## Additional
I've also tested with some components from PrimeVue (Button, Input, Toast), and the load inflated to 728kB and load time was about 9s... 😆