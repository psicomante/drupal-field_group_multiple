<?php


function field_group_multiple_field_ui_overview_form_alter(&$form, &$form_state, $display_overview = FALSE) {
  Logger::log("");

  $form['#validate'][] = "field_group_multiple_field_overview_validate";
  $form['#submit'][] = "field_group_multiple_field_overview_submit";
}

function field_group_multiple_field_overview_validate($form, &$form_state) {
  _field_group_multiple_field_ui_overview_operation($form, $form_state, 'validate');
}


function field_group_multiple_field_overview_submit($form, &$form_state) {
  _field_group_multiple_field_ui_overview_operation($form, $form_state, 'submit');
}


function _field_group_multiple_field_ui_overview_operation($form, &$form_state, $op) {
  Logger::log($op);

  //if(!isset($form_state['field_group_params']) || empty($form_state['field_group_params'])) return;
  //if(!isset($form['#groups']) || empty($form['#groups'])) return;
  //Logger::log($form_state);

  //$field_groups = $form_state['field_group_params']->groups;
  //Logger::log($field_groups);

  if(!isset($form['fields'])) return ;

  $map = array();
  foreach(element_children($form['fields']) as $field_name ){
    if(isset($form['fields'][$field_name]['#row_type']) && $form['fields'][$field_name]['#row_type'] == 'field'){
      if(isset($form['fields'][$field_name]['parent_wrapper']['parent']['#value']) && !empty($form['fields'][$field_name]['parent_wrapper']['parent']['#value'])){
        //$group = $form['fields'][$key]['parent_wrapper']['parent']['#value'];
        $map[$field_name] = $form['fields'][$field_name]['parent_wrapper']['parent']['#value'];

      }
    }

  }

  Logger::log($map);

  if(isset($form_state['values']['fields'])){
      foreach($form_state['values']['fields'] as $field_name => $data){
        if(isset($data['format']['type']) && _is_field_group_multiple($data['format']['type'])){
          $function = '_' . $data['format']['type'] . '_format_' . $op;
          Logger::log($function);
          if(function_exists($function)) {
            Logger::log("exists");
            $group = new stdClass();
            $group->group_name = $field_name;
            $group->format_type = $data['format']['type'];
            $group->children = array_keys($map, $field_name);

            // TODO get children
            $function($form, $form_state, $group);
          }
        }
      }
  }

//   foreach($field_groups as $group_name => $group){
//     if(_is_field_group_multiple($group->format_type)){
//       $function = '_' . $group->format_type . '_format_' . $op;
//       Logger::log($function);
//       if(function_exists($function)) {
//         Logger::log("exists");
//         $function($form, $form_state, $group);
//       }
//     }
//   }

}



/**
 * Default settings
 */
function _field_group_multiple_default_format_settings($group){

}

/**
 * Default summary
 */
function _field_group_multiple_default_format_summary($group){

}

function _field_group_multiple_default_format_validate($form, &$form_state, $group){

}

function _field_group_multiple_default_format_submit($form, &$form_state, $group){

}


/**
 * Table settings
 */
function _field_group_multiple_table_format_settings($group){
  Logger::log("");

  $form = array(
      'instance_settings' => array(
        '#tree' => TRUE,
        '#weight' => 2,
    ),
  );

  $field_group_types = field_group_formatter_info();
  $mode = $group->mode == 'form' ? 'form' : 'display';
  $formatter = $field_group_types[$mode][$group->format_type];

  return $form;
}


function _field_group_multiple_table_format_summary($group){
  $cardinalities = _field_group_multiple_get_fields_infos($group->children, 'cardinality');
  $output = array();
  foreach($cardinalities as $field_name => $value){
    $output[] = $field_name.": ".$value;
  }

  return theme("item_list",array("items"=>$output));
}

function _field_group_multiple_table_format_validate($form, &$form_state, $group){
  _field_group_multiple_default_format_validate($form, $form_state, $group);

  Logger::log($group);
  // TODO differencing between page refresh or save operation
  $cardinalities = _field_group_multiple_get_fields_infos($group->children, 'cardinality');

  if(min($cardinalities) != max($cardinalities)){
    form_set_error("fields[".$group->group_name."][format][type]",print_r($cardinalities,true));
  }


}

function _field_group_multiple_get_fields_infos($field_names, $key){
  $cardinalities = array();
  foreach($field_names as $field_name){
    $instance = field_info_field($field_name);
    $cardinalities[$field_name] = $instance[$key];
  }
  return $cardinalities;

}



function _field_group_multiple_table_format_submit($form, &$form_state, $group){
  _field_group_multiple_default_format_submit($form, $form_state, $group);

  Logger::log("");
}
