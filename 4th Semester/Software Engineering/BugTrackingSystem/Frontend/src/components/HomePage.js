import React from 'react';
import LoginPage from './LoginPage';
import {
    BrowserRouter as Router,
    Routes,
    Route
} from 'react-router-dom';
import MainPage from './MainPage';

export default function HomePage() {
    return (
        <Router>
            <Routes>
                <Route exact path='/' element={<MainPage />} />
                <Route path='/login' element={<LoginPage />} />
            </Routes>
        </Router>
    )
}