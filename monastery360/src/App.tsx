import { Routes, Route, Link } from 'react-router-dom'
import './App.css'

function Home() {
	return (
		<div className="card">
			<h1>Monastery360</h1>
			<p>Explore Sikkim's monasteries through immersive 360° experiences.</p>
			<ul>
				<li>Virtual Tours: 360° panoramic interiors and exteriors</li>
				<li>Narrated walkthroughs: English, Nepali, Hindi, Tibetan</li>
				<li>Interactive Map: Routes, travel times, nearby attractions</li>
			</ul>
			<div style={{ display: 'flex', gap: 12 }}>
				<Link to="/landing" className="button">Go to Landing</Link>
			</div>
		</div>
	)
}

function Landing() {
	return (
		<div className="card">
			<h2>Landing Page</h2>
			<p>Coming soon: Virtual Tours and Interactive Map.</p>
			<div style={{ display: 'grid', gap: 8 }}>
				<div style={{ padding: 12, border: '1px solid #444', borderRadius: 8 }}>
					<strong>Virtual Tour (Placeholder)</strong>
					<div style={{ height: 180, background: '#1e1e1e', display: 'grid', placeItems: 'center', borderRadius: 6 }}>360° Viewer</div>
					<small style={{ color: '#aaa' }}>Pluggable with PhotoSphereViewer or React 360</small>
				</div>
				<div style={{ padding: 12, border: '1px solid #444', borderRadius: 8 }}>
					<strong>Interactive Map (Placeholder)</strong>
					<div style={{ height: 180, background: '#1e1e1e', display: 'grid', placeItems: 'center', borderRadius: 6 }}>Map</div>
					<small style={{ color: '#aaa' }}>Pluggable with MapLibre or Google Maps</small>
				</div>
			</div>
			<Link to="/">Back to Home</Link>
		</div>
	)
}

function Navbar() {
	return (
		<nav style={{ display: 'flex', alignItems: 'center', gap: 16, padding: '12px 16px' }}>
			<Link to="/" style={{ fontWeight: 700 }}>Monastery360</Link>
			<div style={{ marginLeft: 'auto', display: 'flex', gap: 12 }}>
				<Link to="/">Home</Link>
				<Link to="/landing">Landing</Link>
			</div>
		</nav>
	)
}

function App() {
	return (
		<>
			<Navbar />
			<Routes>
				<Route path="/" element={<Home />} />
				<Route path="/landing" element={<Landing />} />
			</Routes>
		</>
	)
}

export default App
