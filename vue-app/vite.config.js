import { fileURLToPath, URL } from 'node:url'

import { defineConfig } from 'vite'
import vue from '@vitejs/plugin-vue'

// https://vitejs.dev/config/
export default defineConfig({
  plugins: [
    vue(),
  ],
	server: { 
		host: '0.0.0.0'
	},
	build: { 
		assetsDir: './', // https://vitejs.dev/config/build-options#build-assetsdir
    rollupOptions: { // https://rollupjs.org/configuration-options/
      output: {
        inlineDynamicImports: false,
        format: 'iife',
        // single output
        manualChunks: () => { 
          return 'same chunk' // all dependencies under the same chunk
        },
        // rename js
        entryFileNames: '[name].min.js', 
        // chunkFileNames: '[name].chunk.js',
      },
    },
	},
  resolve: {
    alias: {
      '@': fileURLToPath(new URL('./src', import.meta.url))
    }
  }
})
