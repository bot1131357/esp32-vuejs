# Example Vue.js app deployment on ESP32

If you just want to get it running, you can start from Step 1.  
See Step 0 if you want to create from scratch.

0) [Starting from scratch)](#from-scratch)
1) [Cloning from repo)](#from-repo)
2) [Deployment](#deploy-vue-app)


# From scratch
## Create a Vue project
```powershell
npm init vue vue-app
cd vue-app
npm install
```


## Build config 
Since SPIFFS runs on a flat file system, we want the output files to be placed in a flat directory structure. Add the following option to `vite.config.js`:
```js
build: { 
  assetsDir: './'
},
```


## Optimization: Dependencies within a chunk
We can gzip our dependencies into a single file and then compress it. Add the following option to `vite.config.js`:
```js
rollupOptions: {
  output: {
    inlineDynamicImports: false,
    format: 'iife',
    // single output
    manualChunks: () => { 
      return 'same chunk'
    },
    // rename js
    entryFileNames: '[name].min.js', 
    // chunkFileNames: '[name].chunk.js',
  },
},
```


## Optimization: Automate the build process
After the build, we want to compress the file to reduce network payload. We do this by using gzip compression. After that we copy them to the `data/` of our esp32 dir. We can automate this process by changing `scripts.build` in `package.json`:
```json
"build": "vite build && 7z a -tgzip dist/index.min.js.gz dist/index.min.js && dir && robocopy dist ..\\platform_io_priv\\data index.html index.min.js.gz",
```
Note 1: I'm using 7z in a Windows environment so you'll have to adapt the command accordingly.
Note 2: I'm using a different esp32 dir `platform_io_priv/` for testing, so in your case it would be `platform_io/`


## Optimization: Serving gzip file
We can gzip our dependencies into a single file and then compress it. Add the following option to `vite.config.js`:
```cpp
server.on("/index.min.js", HTTP_GET, [](AsyncWebServerRequest *request) {
  // request->send(200, "text/plain", "Hello, world");
  
  AsyncWebServerResponse *response = request->beginResponse(SPIFFS, "/index.min.js.gz", "text/javascript");
  response->addHeader("Content-Encoding", "gzip");
  request->send(response);
});
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


## Acknowledgment
Thank you [u/ProgrammaticallySale](https://www.reddit.com/r/esp32/comments/1d9b5o0/comment/l7ehnhm/?utm_source=share&utm_medium=web3x&utm_name=web3xcss&utm_term=1&utm_content=share_button) for the advice on bundling and compression. I learned something new.