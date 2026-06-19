/*
 * Vista simple + portal + error — Maker Campus Microscopio
 * Paleta: Azul #0EA5E9 · Rojo #E63946 · Blanco
 */

const uint8_t index_simple_html[] = R"=====(<!doctype html>
<html lang="es">
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title>Maker Campus | Vista Simple</title>
    <style>
      :root {
        --mc-red:   #E63946;
        --mc-blue:  #0EA5E9;
        --bg:       #050d14;
        --card:     #0f2030;
        --border:   rgba(14,165,233,0.25);
        --border-hi:rgba(14,165,233,0.55);
        --text:     #f0f7ff;
        --muted:    #7fb3cc;
      }
      *, *::before, *::after { box-sizing: border-box; margin: 0; padding: 0; }

      body {
        font-family: -apple-system, "Segoe UI", system-ui, sans-serif;
        background: var(--bg);
        background-image: radial-gradient(ellipse 80% 50% at 50% -10%, rgba(14,165,233,0.12) 0%, transparent 60%);
        color: var(--text);
        min-height: 100dvh;
      }

      main { max-width: 960px; margin: 0 auto; padding: 14px; }

      /* ── Hero ── */
      .hero {
        text-align: center;
        padding: 28px 16px 20px;
        margin-bottom: 14px;
      }
      .mc-logo {
        filter: drop-shadow(0 4px 16px rgba(14,165,233,0.45));
        margin-bottom: 12px;
      }
      .hero-title {
        font-size: 1.1rem;
        font-weight: 700;
        color: var(--text);
      }
      .hero-sub {
        margin-top: 4px;
        font-size: 0.82rem;
        color: var(--muted);
      }

      /* ── Card ── */
      .card {
        border-radius: 16px;
        background: var(--card);
        border: 1px solid var(--border);
        box-shadow: 0 8px 40px rgba(0,0,0,0.45), inset 0 1px 0 rgba(255,255,255,0.04);
        overflow: hidden;
      }

      /* ── Topbar ── */
      .topbar {
        display: flex;
        flex-wrap: wrap;
        align-items: center;
        justify-content: space-between;
        gap: 10px;
        padding: 12px 16px;
        background: rgba(5,13,20,0.6);
        border-bottom: 1px solid var(--border);
        backdrop-filter: blur(8px);
      }
      .topbar-title { font-size: 0.9rem; font-weight: 700; }
      .topbar-sub   { font-size: 0.78rem; color: var(--muted); margin-top: 2px; }

      .toolbar { display: flex; flex-wrap: wrap; gap: 8px; }

      /* ── Buttons ── */
      button {
        display: inline-flex;
        align-items: center;
        gap: 6px;
        border: 0;
        border-radius: 10px;
        padding: 8px 14px;
        font-size: 0.85rem;
        font-weight: 600;
        cursor: pointer;
        transition: filter 0.15s, transform 0.1s;
        color: #fff;
      }
      button:hover  { filter: brightness(1.12); }
      button:active { transform: translateY(1px); }

      .btn-primary   { background: var(--mc-red);  box-shadow: 0 0 14px rgba(230,57,70,0.3); }
      .btn-secondary {
        background: rgba(14,165,233,0.15);
        border: 1px solid rgba(14,165,233,0.35);
        color: var(--mc-blue);
      }
      .btn-secondary:hover { background: rgba(14,165,233,0.28); }

      /* ── Viewer ── */
      .viewer { padding: 12px; }
      .viewer img {
        width: 100%;
        max-height: 72vh;
        object-fit: contain;
        border-radius: 12px;
        background: #000;
        border: 1px solid var(--border-hi);
        box-shadow: 0 0 30px rgba(14,165,233,0.12);
        display: block;
      }
    </style>
  </head>

  <body>
    <main>
      <!-- Logo hero -->
      <div class="hero">
        <svg class="mc-logo" viewBox="0 0 480 320" width="160" height="107">
          <rect x="4" y="4" width="472" height="312" fill="#0EA5E9" rx="12"/>
          <rect x="20" y="20" width="440" height="280" fill="#FFFFFF" rx="6"/>
          <text x="240" y="128" font-family="Arial Black, Arial, sans-serif" font-size="76"
                font-weight="900" fill="#E63946" text-anchor="middle">MAKER</text>
          <text x="240" y="208" font-family="Arial Black, Arial, sans-serif" font-size="76"
                font-weight="900" fill="#E63946" text-anchor="middle">CAMPUS</text>
        </svg>
        <div class="hero-title" id="cam-name">Maker Campus Microscopio UDD</div>
        <div class="hero-sub">Universidad del Desarrollo · Portal de acceso</div>
      </div>

      <!-- Visor -->
      <section class="card">
        <div class="topbar">
          <div>
            <div class="topbar-title">Visor en Vivo</div>
            <div class="topbar-sub">Transmisión de video en directo</div>
          </div>
          <div class="toolbar">
            <button id="btn-full"  class="btn-secondary">Vista Completa</button>
            <button id="btn-lamp"  class="btn-primary">Encender Luz</button>
          </div>
        </div>
        <div class="viewer">
          <img id="stream" alt="Transmisión de cámara">
        </div>
      </section>
    </main>

    <script>
      document.addEventListener('DOMContentLoaded', async () => {
        const base    = document.location.origin;
        const stream  = document.getElementById('stream');
        const btnLamp = document.getElementById('btn-lamp');
        const btnFull = document.getElementById('btn-full');

        const setCtrl = (name, value) =>
          fetch(`${base}/control?var=${encodeURIComponent(name)}&val=${encodeURIComponent(value)}`);

        const state = await fetch(`${base}/status`).then(r => r.json());
        const name  = state.cam_name || 'Maker Campus Microscopio UDD';

        document.getElementById('cam-name').textContent = name;
        document.title = `${name} | Vista Simple`;
        stream.src = state.stream_url;

        let lampOn = Number(state.lamp) > 0;
        const defaultLamp = Number(state.lamp_simple_default || 25);

        const syncLamp = () => {
          btnLamp.textContent = lampOn ? 'Apagar Luz' : 'Encender Luz';
        };
        syncLamp();

        btnLamp.addEventListener('click', async () => {
          lampOn = !lampOn;
          await setCtrl('lamp', lampOn ? defaultLamp : 0);
          syncLamp();
        });

        btnFull.addEventListener('click', () => window.open('/?view=full', '_self'));
      });
    </script>
  </body>
</html>)=====";

size_t index_simple_html_len = sizeof(index_simple_html) - 1;

const std::string portal_html = R"=====(<!doctype html>
<html lang="es">
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title><CAMNAME> | Portal</title>
    <style>
      :root {
        --mc-red:  #E63946;
        --mc-blue: #0EA5E9;
        --bg:      #050d14;
        --card:    #0f2030;
        --border:  rgba(14,165,233,0.25);
        --text:    #f0f7ff;
        --muted:   #7fb3cc;
      }
      *, *::before, *::after { box-sizing: border-box; margin: 0; padding: 0; }
      body {
        font-family: -apple-system, "Segoe UI", system-ui, sans-serif;
        background: var(--bg);
        background-image: radial-gradient(ellipse 80% 50% at 50% -10%, rgba(14,165,233,0.12) 0%, transparent 60%);
        color: var(--text);
        min-height: 100dvh;
        display: flex;
        align-items: center;
        justify-content: center;
      }
      .wrap {
        max-width: 520px;
        width: 100%;
        margin: 24px;
        text-align: center;
        background: var(--card);
        border: 1px solid var(--border);
        border-radius: 20px;
        padding: 36px 28px;
        box-shadow: 0 16px 60px rgba(0,0,0,0.55);
      }
      .mc-logo { filter: drop-shadow(0 4px 16px rgba(14,165,233,0.45)); margin-bottom: 20px; }
      h1 { font-size: 1.2rem; font-weight: 700; margin-bottom: 6px; }
      p  { font-size: 0.88rem; color: var(--muted); margin-bottom: 24px; }
      .actions { display: flex; justify-content: center; flex-wrap: wrap; gap: 10px; }
      a { text-decoration: none; }
      button {
        border: 0; border-radius: 10px;
        padding: 10px 22px;
        font-size: 0.9rem; font-weight: 600;
        cursor: pointer; color: #fff;
        background: var(--mc-red);
        box-shadow: 0 0 16px rgba(230,57,70,0.35);
        transition: filter 0.15s, transform 0.1s;
      }
      button:hover  { filter: brightness(1.12); }
      button:active { transform: translateY(1px); }
    </style>
  </head>
  <body>
    <div class="wrap">
      <svg class="mc-logo" viewBox="0 0 480 320" width="140" height="93">
        <rect x="4" y="4" width="472" height="312" fill="#0EA5E9" rx="12"/>
        <rect x="20" y="20" width="440" height="280" fill="#FFFFFF" rx="6"/>
        <text x="240" y="128" font-family="Arial Black, Arial, sans-serif" font-size="76"
              font-weight="900" fill="#E63946" text-anchor="middle">MAKER</text>
        <text x="240" y="208" font-family="Arial Black, Arial, sans-serif" font-size="76"
              font-weight="900" fill="#E63946" text-anchor="middle">CAMPUS</text>
      </svg>
      <h1><CAMNAME></h1>
      <p>Portal de acceso · Universidad del Desarrollo</p>
      <div class="actions">
        <a href="<APPURL>?view=full" target="_blank"><button>Abrir Microscopio</button></a>
      </div>
    </div>
  </body>
</html>)=====";

const std::string error_html = R"=====(<!doctype html>
<html lang="es">
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <title><CAMNAME> | Error</title>
    <style>
      :root {
        --mc-red:  #E63946;
        --mc-blue: #0EA5E9;
        --bg:      #050d14;
        --text:    #f0f7ff;
        --muted:   #7fb3cc;
      }
      *, *::before, *::after { box-sizing: border-box; margin: 0; padding: 0; }
      body {
        font-family: -apple-system, "Segoe UI", system-ui, sans-serif;
        background: var(--bg);
        color: var(--text);
        min-height: 100dvh;
        display: flex;
        align-items: center;
        justify-content: center;
        text-align: center;
      }
      .wrap { max-width: 480px; margin: 24px; padding: 32px; }
      .icon { font-size: 3rem; margin-bottom: 16px; }
      h1 { font-size: 1.15rem; margin-bottom: 8px; }
      p  { font-size: 0.85rem; color: var(--muted); }
    </style>
  </head>
  <body>
    <div class="wrap">
      <div class="icon">⚠️</div>
      <h1><CAMNAME></h1>
      <ERRORTEXT>
      <p style="margin-top:16px">Reintentando en 60 segundos…</p>
    </div>
    <script>setTimeout(() => location.replace(document.URL), 60000);</script>
  </body>
</html>)=====";
