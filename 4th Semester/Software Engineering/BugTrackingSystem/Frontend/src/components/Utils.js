import {
    AddBox, ArrowDownward,
    Check, ChevronLeft,
    ChevronRight,
    Clear,
    DeleteOutline,
    Edit,
    FilterList,
    FirstPage, LastPage, Remove,
    SaveAlt, Search, ViewColumn
} from '@material-ui/icons';
import React, { forwardRef } from 'react';

export const tableIcons = {
  Add: forwardRef((props, ref) => <AddBox {...props} ref={ref} />),
  Check: forwardRef((props, ref) => <Check {...props} ref={ref} />),
  Clear: forwardRef((props, ref) => <Clear {...props} ref={ref} />),
  Delete: forwardRef((props, ref) => <DeleteOutline {...props} ref={ref} />),
  DetailPanel: forwardRef((props, ref) => <ChevronRight {...props} ref={ref} />),
  Edit: forwardRef((props, ref) => <Edit {...props} ref={ref} />),
  Export: forwardRef((props, ref) => <SaveAlt {...props} ref={ref} />),
  Filter: forwardRef((props, ref) => <FilterList {...props} ref={ref} />),
  FirstPage: forwardRef((props, ref) => <FirstPage {...props} ref={ref} />),
  LastPage: forwardRef((props, ref) => <LastPage {...props} ref={ref} />),
  NextPage: forwardRef((props, ref) => <ChevronRight {...props} ref={ref} />),
  PreviousPage: forwardRef((props, ref) => <ChevronLeft {...props} ref={ref} />),
  ResetSearch: forwardRef((props, ref) => <Clear {...props} ref={ref} />),
  Search: forwardRef((props, ref) => <Search {...props} ref={ref} />),
  SortArrow: forwardRef((props, ref) => <ArrowDownward {...props} ref={ref} />),
  ThirdStateCheck: forwardRef((props, ref) => <Remove {...props} ref={ref} />),
  ViewColumn: forwardRef((props, ref) => <ViewColumn {...props} ref={ref} />)
};

import {
    ContactSupport,
    Pause,
    DoneAll
} from '@material-ui/icons';
import {Chip} from "@material-ui/core";

export const renderStatus = (status) => {
    let color = 'default', label = 'Unknown', icon = <ContactSupport />;
    switch (status) {
    case 'unassigned':
      label = 'unassigned';
      icon = <Pause />;
      break;
    case 'assigned':
      color = 'secondary';
      label = 'assigned';
      icon = <Search />;
      break;
    case 'fixed':
      color = 'primary';
      label = 'fixed';
      icon = <DoneAll />
      break;
    default:
      break;
    }
    return <Chip label={label} color={color} icon={icon} />;
}