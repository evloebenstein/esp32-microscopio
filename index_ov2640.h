/*
 * Vista full — Maker Campus Microscopio
 * Paleta: Azul #0EA5E9 · Rojo #E63946 · Blanco
 */

const uint8_t index_ov2640_html[] = R"=====(<!doctype html>
<html lang="es">
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Maker Campus | Microscopio</title>
    <style>
      :root {
        --mc-red:    #E63946;
        --mc-blue:   #0EA5E9;
        --bg:        #050d14;
        --card:      #0f2030;
        --card-alt:  #0b1a29;
        --border:    rgba(14,165,233,0.22);
        --border-hi: rgba(14,165,233,0.5);
        --text:      #f0f7ff;
        --muted:     #7fb3cc;
        --input-bg:  #071622;
      }

      *, *::before, *::after { box-sizing: border-box; margin: 0; padding: 0; }

      body {
        font-family: -apple-system, "Segoe UI", system-ui, sans-serif;
        background: var(--bg);
        background-image:
          radial-gradient(ellipse 80% 40% at 50% -5%, rgba(14,165,233,0.10) 0%, transparent 60%);
        color: var(--text);
        min-height: 100dvh;
      }

      /* ── Layout dos columnas ── */
      .layout {
        max-width: 1300px;
        margin: 0 auto;
        padding: 14px;
        display: grid;
        grid-template-columns: 1fr;
        gap: 14px;
      }
      @media (min-width: 960px) {
        .layout { grid-template-columns: 1fr 320px; align-items: start; }
      }

      /* ── Card base ── */
      .card {
        border-radius: 14px;
        background: var(--card);
        border: 1px solid var(--border);
        box-shadow: 0 8px 36px rgba(0,0,0,0.5), inset 0 1px 0 rgba(255,255,255,0.03);
        overflow: hidden;
      }

      /* ── Topbar: solo logo + nombre ── */
      .topbar {
        display: flex;
        align-items: center;
        gap: 12px;
        padding: 11px 16px;
        background: rgba(4,10,18,0.75);
        border-bottom: 1px solid var(--border);
      }

      .mc-logo { flex-shrink: 0; filter: drop-shadow(0 2px 6px rgba(14,165,233,0.35)); }

      .brand-text h1 {
        font-size: 0.92rem;
        font-weight: 700;
        color: var(--text);
        line-height: 1.2;
      }
      .brand-text .subtitle {
        font-size: 0.75rem;
        color: var(--muted);
        margin-top: 1px;
      }

      /* ── Viewer ── */
      .viewer { padding: 12px 12px 0; }
      .viewer img {
        width: 100%;
        max-height: 62vh;
        object-fit: contain;
        border-radius: 10px;
        background: #000;
        border: 1px solid var(--border-hi);
        box-shadow: 0 0 28px rgba(14,165,233,0.10);
        display: block;
      }

      /* ── Action bar: debajo del video, ancho completo ── */
      .action-bar {
        display: grid;
        grid-template-columns: 1fr 1fr;
        gap: 10px;
        padding: 12px;
      }

      /* ── Buttons ── */
      button {
        display: inline-flex;
        align-items: center;
        justify-content: center;
        gap: 7px;
        border: 0;
        border-radius: 10px;
        padding: 11px 18px;
        font-size: 0.88rem;
        font-weight: 700;
        letter-spacing: 0.02em;
        cursor: pointer;
        transition: filter 0.15s, transform 0.1s, box-shadow 0.15s;
        color: #fff;
      }
      button:hover  { filter: brightness(1.12); }
      button:active { transform: translateY(1px); }

      .btn-stream {
        background: var(--mc-red);
        box-shadow: 0 0 16px rgba(230,57,70,0.28);
      }
      .btn-capture {
        background: rgba(14,165,233,0.15);
        border: 1px solid var(--border-hi);
        color: var(--mc-blue);
      }
      .btn-capture:hover { background: rgba(14,165,233,0.26); }

      /* Perfil buttons — iguales entre sí */
      .btn-profile {
        flex: 1;
        background: rgba(14,165,233,0.10);
        border: 1px solid var(--border);
        color: var(--muted);
        font-size: 0.82rem;
        padding: 7px 0;
        border-radius: 8px;
      }
      .btn-profile.btn-active {
        background: rgba(14,165,233,0.22);
        border-color: var(--mc-blue);
        color: var(--mc-blue);
        box-shadow: 0 0 8px rgba(14,165,233,0.2);
      }

      /* ── Controls panel ── */
      .controls-panel {
        padding: 12px;
        display: flex;
        flex-direction: column;
        gap: 10px;
      }

      /* ── Group card dentro del panel ── */
      .group {
        border-radius: 10px;
        border: 1px solid var(--border);
        background: rgba(7,22,34,0.6);
        overflow: hidden;
      }

      .group-header {
        padding: 8px 13px;
        background: rgba(14,165,233,0.08);
        border-bottom: 1px solid var(--border);
        font-size: 0.72rem;
        font-weight: 800;
        letter-spacing: 0.09em;
        text-transform: uppercase;
        color: var(--mc-blue);
      }

      .group-body {
        padding: 11px 13px;
        display: flex;
        flex-direction: column;
        gap: 10px;
      }

      /* ── Perfiles: fila uniforme ── */
      .profile-row {
        display: flex;
        gap: 6px;
      }

      /* ── Status line ── */
      .status-line {
        font-size: 0.72rem;
        color: var(--muted);
        line-height: 1.5;
        min-height: 18px;
      }

      /* ── Slider rows ── */
      .ctrl-row {
        display: grid;
        grid-template-columns: 82px 1fr 36px;
        align-items: center;
        gap: 8px;
      }
      .ctrl-row label {
        font-size: 0.8rem;
        color: var(--muted);
        white-space: nowrap;
      }
      .ctrl-val {
        font-size: 0.8rem;
        color: var(--mc-blue);
        font-weight: 700;
        text-align: right;
      }

      /* ── Range input ── */
      input[type="range"] {
        -webkit-appearance: none;
        width: 100%;
        height: 4px;
        border-radius: 4px;
        background: rgba(14,165,233,0.18);
        outline: none;
        cursor: pointer;
        accent-color: var(--mc-blue);
      }
      input[type="range"]::-webkit-slider-thumb {
        -webkit-appearance: none;
        width: 15px;
        height: 15px;
        border-radius: 50%;
        background: var(--mc-blue);
        box-shadow: 0 0 6px rgba(14,165,233,0.65);
        cursor: pointer;
      }

      /* ── Select / dropdown ── */
      .select-wrap {
        position: relative;
        display: flex;
        flex-direction: column;
        gap: 5px;
      }
      .select-label {
        font-size: 0.8rem;
        color: var(--muted);
      }
      select {
        width: 100%;
        background: var(--input-bg);
        border: 1px solid var(--border-hi);
        border-radius: 8px;
        color: var(--text);          /* texto visible en la caja */
        padding: 7px 10px;
        font-size: 0.82rem;
        font-family: inherit;
        outline: none;
        cursor: pointer;
        appearance: none;
        -webkit-appearance: none;
        /* flecha manual */
        background-image: url("data:image/svg+xml,%3Csvg xmlns='http://www.w3.org/2000/svg' width='12' height='8' viewBox='0 0 12 8'%3E%3Cpath d='M1 1l5 5 5-5' stroke='%230EA5E9' stroke-width='1.8' fill='none' stroke-linecap='round'/%3E%3C/svg%3E");
        background-repeat: no-repeat;
        background-position: right 10px center;
        padding-right: 30px;
      }
      select:focus { border-color: var(--mc-blue); }
      /* Opciones del dropdown nativo */
      select option {
        background: #0b1d2e;
        color: #f0f7ff;
      }
    </style>
  </head>

  <body>
    <main class="layout">

      <!-- ═══ CÁMARA ═══ -->
      <section class="card">
        <!-- Logo + nombre -->
        <div class="topbar">
          <svg class="mc-logo" viewBox="0 0 480 320" width="52" height="35">
            <rect x="4" y="4" width="472" height="312" fill="#0EA5E9" rx="10"/>
            <rect x="20" y="20" width="440" height="280" fill="#FFFFFF" rx="5"/>
            <text x="240" y="122" font-family="Arial Black,Arial,sans-serif" font-size="68"
                  font-weight="900" fill="#E63946" text-anchor="middle">MAKER</text>
            <text x="240" y="196" font-family="Arial Black,Arial,sans-serif" font-size="68"
                  font-weight="900" fill="#E63946" text-anchor="middle">CAMPUS</text>
          </svg>
          <div class="brand-text">
            <h1 id="cam-name">Maker Campus Microscopio</h1>
            <div class="subtitle" id="fw">Universidad del Desarrollo</div>
          </div>
        </div>

        <!-- Stream -->
        <div class="viewer">
          <img id="stream" alt="Transmision de camara">
        </div>

        <!-- Botones de accion — anchos, debajo del video -->
        <div class="action-bar">
          <button id="btn-stream" class="btn-stream">Iniciar Stream</button>
          <button id="btn-capture" class="btn-capture">Capturar Foto</button>
        </div>
      </section>

      <!-- ═══ CONTROLES ═══ -->
      <aside class="card controls-panel">

        <!-- Perfiles -->
        <div class="group">
          <div class="group-header">Perfil de Calidad</div>
          <div class="group-body">
            <div class="profile-row">
              <button id="profile-low"    class="btn-profile">Bajo</button>
              <button id="profile-medium" class="btn-profile">Medio</button>
              <button id="profile-high"   class="btn-profile">Alto</button>
            </div>
            <div class="status-line" id="profile-info"></div>
          </div>
        </div>

        <!-- Iluminacion -->
        <div class="group">
          <div class="group-header">Iluminacion</div>
          <div class="group-body">
            <div class="ctrl-row">
              <label for="lamp">Flashlight</label>
              <input id="lamp" type="range" min="0" max="80" step="1" value="0">
              <span class="ctrl-val" id="lamp-value">0%</span>
            </div>
          </div>
        </div>

        <!-- Imagen -->
        <div class="group">
          <div class="group-header">Ajustes de Imagen</div>
          <div class="group-body">
            <div class="ctrl-row">
              <label for="brightness">Brillo</label>
              <input id="brightness" type="range" min="-3" max="3" step="1" value="0">
              <span class="ctrl-val" id="brightness-value">0</span>
            </div>
            <div class="ctrl-row">
              <label for="contrast">Contraste</label>
              <input id="contrast" type="range" min="-3" max="3" step="1" value="0">
              <span class="ctrl-val" id="contrast-value">0</span>
            </div>
            <div class="ctrl-row">
              <label for="saturation">Saturacion</label>
              <input id="saturation" type="range" min="-4" max="4" step="1" value="0">
              <span class="ctrl-val" id="saturation-value">0</span>
            </div>
            <div class="select-wrap">
              <span class="select-label">Filtro de color</span>
              <select id="special_effect">
                <option value="0">Sin filtro</option>
                <option value="1">Negativo</option>
                <option value="2">Escala de grises</option>
                <option value="3">Tinte rojo</option>
                <option value="4">Tinte verde</option>
                <option value="5">Tinte azul</option>
                <option value="6">Sepia</option>
              </select>
            </div>
          </div>
        </div>

      </aside>
    </main>

    <script>
      document.addEventListener('DOMContentLoaded', async () => {
        const $ = id => document.getElementById(id);
        const setText = (el, v) => { if (el) el.textContent = v; };

        const base       = document.location.origin;
        const streamImg  = $('stream');
        const btnStream  = $('btn-stream');
        const btnCapture = $('btn-capture');

        const lamp       = $('lamp');
        const brightness = $('brightness');
        const contrast   = $('contrast');
        const saturation = $('saturation');
        const specialFx  = $('special_effect');

        const profileBtns = {
          low:    $('profile-low'),
          medium: $('profile-medium'),
          high:   $('profile-high')
        };

        const setCtrl = (name, value) =>
          fetch(`${base}/control?var=${encodeURIComponent(name)}&val=${encodeURIComponent(value)}`);

        let streaming = false;
        let streamUrl = '';

        const stopStream = () => {
          window.stop();
          streamImg.removeAttribute('src');
          streaming = false;
          setText(btnStream, 'Iniciar Stream');
        };

        const startStream = () => {
          if (!streamUrl) return;
          streamImg.src = streamUrl;
          streaming = true;
          setText(btnStream, 'Detener Stream');
        };

        const markProfile = (key, label, fs, qPct, xclk) => {
          Object.values(profileBtns).forEach(b => b && b.classList.remove('btn-active'));
          if (profileBtns[key]) profileBtns[key].classList.add('btn-active');
          setText($('profile-info'), label
            ? `${label}  |  ${fs}  |  Calidad ${qPct}%  |  ${xclk} MHz`
            : '');
        };

        /* Init */
        try {
          const s = await fetch(`${base}/status`).then(r => r.json());
          const name = s.cam_name || 'Maker Campus Microscopio';
          setText($('cam-name'), name);
          document.title = `${name} | Microscopio`;

          streamUrl = s.stream_url || '';

          if (lamp)       { lamp.max = s.lamp_max ?? 80; lamp.value = s.lamp ?? 0; }
          if (brightness)   brightness.value = s.brightness  ?? 0;
          if (contrast)     contrast.value   = s.contrast    ?? 0;
          if (saturation)   saturation.value = s.saturation  ?? 0;
          if (specialFx && s.special_effect != null) specialFx.value = String(s.special_effect);

          setText($('lamp-value'),       `${s.lamp ?? 0}%`);
          setText($('brightness-value'), String(s.brightness  ?? 0));
          setText($('contrast-value'),   String(s.contrast    ?? 0));
          setText($('saturation-value'), String(s.saturation  ?? 0));

          markProfile(s.profile_key, s.profile_label, s.framesize_name, s.quality_pct, s.xclk);
          startStream();
        } catch (e) {
          console.error('Error al iniciar vista full:', e);
        }

        /* Stream toggle */
        btnStream?.addEventListener('click', () => streaming ? stopStream() : startStream());

        /* Capture */
        btnCapture?.addEventListener('click', () => {
          const a = Object.assign(document.createElement('a'), {
            href: `${base}/capture?_cb=${Date.now()}`,
            download: `mc_${Date.now()}.jpg`
          });
          document.body.appendChild(a); a.click(); document.body.removeChild(a);
        });

        /* Sliders */
        const bindSlider = (el, valEl, suffix, ctrlName) => {
          if (!el) return;
          el.addEventListener('input',  () => setText(valEl, el.value + suffix));
          el.addEventListener('change', () => setCtrl(ctrlName, el.value));
        };
        bindSlider(lamp,       $('lamp-value'),       '%', 'lamp');
        bindSlider(brightness, $('brightness-value'), '',  'brightness');
        bindSlider(contrast,   $('contrast-value'),   '',  'contrast');
        bindSlider(saturation, $('saturation-value'), '',  'saturation');

        specialFx?.addEventListener('change', () => setCtrl('special_effect', specialFx.value));

        /* Profiles */
        for (const [key, btn] of Object.entries(profileBtns)) {
          if (!btn) continue;
          btn.addEventListener('click', async () => {
            await setCtrl('profile', key);
            const s = await fetch(`${base}/status`).then(r => r.json());
            if (lamp && s.lamp != null) { lamp.value = s.lamp; setText($('lamp-value'), `${s.lamp}%`); }
            markProfile(s.profile_key, s.profile_label, s.framesize_name, s.quality_pct, s.xclk);
            if (!streaming) streamImg.src = `${base}/capture?_cb=${Date.now()}`;
          });
        }
      });
    </script>
  </body>
</html>)=====";

size_t index_ov2640_html_len = sizeof(index_ov2640_html) - 1;
