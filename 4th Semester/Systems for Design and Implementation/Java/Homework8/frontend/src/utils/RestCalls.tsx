import {RIDES_BASE_URL} from "./Consts";
import Ride from "../models/Ride";



export function GetAllRides(): Promise<Ride[]> {
    return fetch(RIDES_BASE_URL, {
        method: 'GET',
        headers: {'Accept': 'application/json'},
        mode: 'cors'
    }).then(status).then(json)
        .then(data => data)
        .catch(error => window.alert(error));
}

export function AddRide(ride: Ride): Promise<Ride> {
    return fetch(RIDES_BASE_URL, {
        method: 'POST',
        headers: {'Content-Type': 'application/json', 'Accept': 'application/json'},
        mode: 'cors',
        body: JSON.stringify(ride)
    }).then(status).then(json)
        .then(data => data)
        .catch(error => window.alert(error));
}

export function UpdateRide(ride: Ride): Promise<Ride> {
    return fetch(`${RIDES_BASE_URL}/${ride.id}`, {
        method: 'PUT',
        headers: {'Content-Type': 'application/json', 'Accept': 'application/json'},
        mode: 'cors',
        body: JSON.stringify(ride)
    }).then(status).then(json)
        .then(data => data)
        .catch(error => window.alert(error));
}

export function DeleteRide(ride: Ride): Promise<Ride> {
    return fetch(`${RIDES_BASE_URL}/${ride.id}`, {
        method: 'DELETE',
        headers: {'Accept': 'application/json'},
        mode: 'cors'
    }).then(status).then(json)
        .then(data => data)
        .catch(error => window.alert(error));
}

function json(response: Response) {
    return response.json();
}

function status(response: Response) {
    if (response.status >= 200 && response.status < 300) {
        return Promise.resolve(response);
    } else {
        return Promise.reject(`ERROR ${response.status}`);
    }
}
